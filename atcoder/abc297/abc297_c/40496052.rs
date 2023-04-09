use proconio::marker::Chars;

fn main() {
    proconio::input! {
        h: usize, w: usize,
        mut s: [Chars; h],
    }

    for i in 0..h {
        for j in 0..w - 1 {
            if s[i][j] == 'T' && s[i][j + 1] == 'T' {
                s[i][j] = 'P';
                s[i][j + 1] = 'C';
            }
        }
    }
    for l in &s {
        println!("{}", l.iter().collect::<String>());
    }
}
