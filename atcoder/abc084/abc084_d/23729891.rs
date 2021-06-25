use proconio::input;
use std::collections::HashSet;

fn main() {
    input! {q: usize}
    let mut cs = vec![0; 100001];
    let ma: usize = 100001;
    let mut prime = HashSet::new();
    let mut cnt = vec![false; ma];
    for i in 2..ma {
        if cnt[i] {
            continue;
        }
        let mut k: usize = 2;
        while i * k < ma {
            cnt[i * k] = true;
            k += 1
        }
    }
    for i in 2..ma {
        if !cnt[i] {
            prime.insert(i);
        }
    }

    for i in 1..ma {
        if i % 2 == 0 {
            continue;
        }
        if prime.contains(&i) && prime.contains(&((i + 1) / 2)) {
            cs[i] += 1;
        }
    }
    for i in 1..ma {
        cs[i] += cs[i - 1];
    }
    for _ in 0..q {
        input! {
            l:usize,
            r: usize
        }
        let ans = cs[r] - cs[l - 1];
        println!("{}", ans);
    }
}
