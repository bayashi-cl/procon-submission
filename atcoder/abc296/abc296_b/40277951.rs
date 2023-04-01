use proconio::marker::Chars;
fn main() {
    proconio::input! {
        s: [Chars; 8]
    }
    for i in 0..8_usize {
        for j in 0..8_usize {
            if s[i][j] == '*' {
                let r = 8 - i;
                let c = ('a' as u8 + j as u8) as char;

                println!("{}{}", c, r);
                return;
            }
        }
    }
    unreachable!();
}
