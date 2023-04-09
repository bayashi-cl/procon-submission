fn main() {
    proconio::input! {
        s: proconio::marker::Chars,
    }
    let mut b = Vec::new();
    let mut r = Vec::new();
    let mut k = 0;
    for i in 0..s.len() {
        match s[i] {
            'B' => {
                b.push(i);
            }
            'R' => {
                r.push(i);
            }
            'K' => {
                k = i;
            }
            _ => {}
        }
    }
    let mut ans = true;
    if b[0] % 2 == b[1] % 2 {
        ans = false;
    }
    if !(r[0] < k && k < r[1]) {
        ans = false;
    }

    println!("{}", if ans { "Yes" } else { "No" });
}
