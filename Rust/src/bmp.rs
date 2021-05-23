use std::fs::File;
use std::io::{Result, Write, BufWriter};

const FILE_TYPE:            u16 = 0x4D42;
const FILE_HEADER_SIZE:     u32 = 14; /* BMPファイルヘッダサイズ */
const INFO_HEADER_SIZE:     u32 = 40; /* Windowsヘッダサイズ */
const DEFAULT_HEADER_SIZE:  u32 = FILE_HEADER_SIZE + INFO_HEADER_SIZE; /* 標準のヘッダサイズ */

#[repr(packed)]
struct BitmapFileHeader {
    _bf_type:       u16,
    _bf_size:       u32,
    _bf_reserved1:  u16,
    _bf_reserved2:  u16,
    _bf_off_bits:   u32
}

#[repr(packed)]
struct BitmapInfoHeader {
    _bi_size:               u32,
    _bi_width:              u32,
    _bi_height:             u32,
    _bi_planes:             u16,
    _bi_bit_count:          u16,
    _bi_compression:        u32,
    _bi_size_image:         u32,
    _bi_x_pix_per_meter:    u32,
    _bi_y_pix_per_meter:    u32,
    _bi_clr_used:           u32,
    _bi_clr_important:      u32
}

unsafe fn any_as_u8_slice<T: Sized>(p: &T) -> &[u8] {
    ::std::slice::from_raw_parts(
        (p as *const T) as *const u8,
        ::std::mem::size_of::<T>(),
    )
}

pub fn write_bmp(mut size: usize, img: Vec<u8>) -> Result<()> {
    size /= 3;

    let width = (size as f64).sqrt() as u32;
    let height = width;

    let stride = (width * 3 + 3) / 4 * 4;

    let file = BitmapFileHeader {
        _bf_type:       FILE_TYPE,
        _bf_size:       DEFAULT_HEADER_SIZE + stride * height,
        _bf_reserved1:  0,
        _bf_reserved2:  0,
        _bf_off_bits:   DEFAULT_HEADER_SIZE
    };

    let info = BitmapInfoHeader {
        _bi_size:               INFO_HEADER_SIZE,
        _bi_width:              width,
        _bi_height:             height,
        _bi_planes:             1,
        _bi_bit_count:          24,
        _bi_compression:        0,
        _bi_size_image:         stride * height,
        _bi_x_pix_per_meter:    0,
        _bi_y_pix_per_meter:    0,
        _bi_clr_used:           0,
        _bi_clr_important:      0
    };

    let mut bmp = BufWriter::new(File::create("result.bmp")?);

    bmp.write_all(unsafe{any_as_u8_slice(&file)})?;
    bmp.write_all(unsafe{any_as_u8_slice(&info)})?;

    let mut buf = Vec::<u8>::with_capacity(stride as usize);
    unsafe{buf.set_len(stride as usize);}

    for y in 0..height {
        for x in 0..(3 * width as usize) {
            buf[x] = img[(3 * width * y) as usize + x];
        }
        bmp.write_all(&buf)?;
    }
    Ok(())
}