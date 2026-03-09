# Định nghĩa các biến đường dẫn
IDIR = include
SDIR = src
ODIR = obj
CC = g++

# Cờ biên dịch: -I$(IDIR) để tìm header trong include/
# Lưu ý: Khi biên dịch nội bộ src, ta sẽ thêm cả src vào đường dẫn include
CFLAGS = -I$(IDIR) -I$(SDIR)

# Mục tiêu: Tạo ra thư viện tĩnh libAudioFX.a
libAudioFX.a: $(ODIR)/AudioFX.o
	ar rcs libAudioFX.a $(ODIR)/AudioFX.o

# Quy tắc tạo file .o từ file .cpp
$(ODIR)/AudioFX.o: $(SDIR)/AudioFX.cpp
	@mkdir -p $(ODIR)
	$(CC) -c $(SDIR)/AudioFX.cpp -o $(ODIR)/AudioFX.o $(CFLAGS)

clean:
	rm -rf $(ODIR) *.a