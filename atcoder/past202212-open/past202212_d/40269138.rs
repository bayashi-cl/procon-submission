use itertools::Itertools;
use proconio::input;

fn main() {
    input! {
        n: usize,
        m: usize,
        s: proconio::marker::Chars,
    }

    let mut cnt = vec![0; n];
    let mut field = 0;
    for i in 0..m {
        let idx = i % n;
        cnt[idx] += 1;
        match s[i] {
            '+' => {
                cnt[idx] += field;
                field = 0;
            }
            '0' => {}
            '-' => {
                field += cnt[idx];
                cnt[idx] = 0;
            }
            _ => unreachable!(),
        }
    }

    println!("{}", cnt.iter().join("\n"));
}
