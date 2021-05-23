mod bmp;

use std::env;
use std::fs::File;
use std::io::{Result, Read};

fn read_file(path:&mut String) -> Result<Vec<u8>> {
    let mut file = File::open(&path)?;

    let mut buf = Vec::new();
    file.read_to_end(&mut buf)?;

    Ok(buf)
}

fn main() -> Result<()> {
    let mut args: Vec<String> = env::args().collect();
    let buf = read_file(&mut args[1])?;
    bmp::write_bmp(buf.len(), buf)?;
    Ok(())
}