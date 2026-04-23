#include <linux/module.h>       
#include <linux/kernel.h>      
#include <linux/io.h>          
#include <linux/platform_device.h> 
#include <linux/timer.h>      
#include <linux/of.h>           
#include <linux/slab.h>        

//OFF SET
#define GPIO_OE_OFFSET           0x134  //đầu ra output(0),input(1)
#define GPIO_SETDATAOUT_OFFSET   0x194   //set bật led
#define GPIO_CLEARDATAOUT_OFFSET 0x190   //set tắt led

//struct data driver
struct my_led_data {
    void __iomem *base_addr;    //địa chỉ ảo
    struct timer_list timer; //thời gian lặp lại
    u32 pin_bit;                //bit tương ứng chân led
    bool led_state;             //trạng thái led
};

//HÀM XỬ LÝ NHÁY LED (TIMER CALLBACK)
static void led_timer_callback(struct timer_list *t) {
    //lấy địa chỉ khối my_led_data
    struct my_led_data *data = from_timer(data, t, timer);
    //nháy led
    if (data->led_state) {
        writel(data->pin_bit, data->base_addr + GPIO_CLEARDATAOUT_OFFSET);
    } else {
        writel(data->pin_bit, data->base_addr + GPIO_SETDATAOUT_OFFSET);
    }

    //dao trang thai
    data->led_state = !data->led_state;

    //hen gio cho 1 giay sau
    mod_timer(&data->timer, jiffies + HZ);
}

//ham probe khoi tao driver
static int led_probe(struct platform_device *pdev) {
    struct resource *res;
    struct my_led_data *data;
    u32 reg_val;

    printk(KERN_INFO "My LED Driver: Dang khoi tao...\n");

    //cấp phát bộ nhớ
    data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
    if (!data) return -ENOMEM;

    //lấy địa chỉ vật lí từ device tree
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) return -EINVAL;

    //ánh xạ địa chỉ
    data->base_addr = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(data->base_addr)) return PTR_ERR(data->base_addr);

    /* Cấu hình chân LED (Ví dụ chân 30 của cụm GPIO) */
    data->pin_bit = (1 << 30); 
    
    /* Cài đặt hướng là OUTPUT: Đọc thanh ghi OE -> Xóa bit 30 về 0 -> Ghi lại */
    reg_val = readl(data->base_addr + GPIO_OE_OFFSET);
    reg_val &= ~(data->pin_bit); 
    writel(reg_val, data->base_addr + GPIO_OE_OFFSET);

    /* Thiết lập Timer lần đầu */
    timer_setup(&data->timer, led_timer_callback, 0);
    mod_timer(&data->timer, jiffies + HZ);

    /* Lưu dữ liệu vào platform device để dùng khi gỡ driver */
    platform_set_drvdata(pdev, data);

    return 0;
}

//go driver
static int led_remove(struct platform_device *pdev) {
    struct my_led_data *data = platform_get_drvdata(pdev);
    //xoa timer
    del_timer_sync(&data->timer);
    //tat led    
    writel(data->pin_bit, data->base_addr + GPIO_CLEARDATAOUT_OFFSET);
    printk(KERN_INFO "My LED Driver: Da go bo thành công.\n");
    return 0;
}

//khai bao node trong device tree
static const struct of_device_id led_of_match[] = {
    { .compatible = "beagle,my-blink-led" },
    { },
};
MODULE_DEVICE_TABLE(of, led_of_match);

//platform driver
static struct platform_driver my_led_driver = {
    .probe = led_probe,
    .remove = led_remove,
    .driver = {
        .name = "my_blink_led",
        .of_match_table = led_of_match,
    },
};

//dang ki driver voi kernel
module_platform_driver(my_led_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hieu");
MODULE_DESCRIPTION("Driver nhay LED cho BeagleBone Black");