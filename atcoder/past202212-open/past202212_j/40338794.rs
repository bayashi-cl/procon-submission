use proconio::input;

fn main() {
    input! {
        n:i64, k:i64,
        sx: i64, sy: i64, tx: i64, ty: i64,
        pqrw: [[i64; 4]; n],
    }

    let mut ws = Vec::new();
    for l in &pqrw {
        match l.as_slice() {
            [p, q, r, w] => {
                let s = *p * sx + *q * sy;
                let t = *p * tx + *q * ty;
                if s == *r || t == *r || (s < *r) ^ (t < *r) {
                    ws.push(*w)
                }
            }
            _ => unreachable!(),
        };
    }
    ws.sort();
    let n_choice = std::cmp::max(k - (n - ws.len() as i64), 0) as usize;
    let mut ans = 0_i64;
    for i in 0..n_choice {
        ans += ws[i];
    }
    println!("{}", ans);
}
