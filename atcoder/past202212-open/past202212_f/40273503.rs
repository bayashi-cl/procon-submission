fn ceil_div(a: i64, b: i64) -> i64 {
    return (a + b - 1) / b;
}

fn main() {
    proconio::input! {
        n: i64,
        a: i64,
        b: i64,
        c: i64,
        d: i64,
        xs: String,
    }

    let s = (a + 2 * b + 3 * c + 4 * d) * 1000;
    let x_lr: Vec<_> = xs.split('.').collect();
    let l = x_lr[0].parse::<i64>().unwrap();
    let r = x_lr[1].parse::<i64>().unwrap();
    let x = l * 1000 + r;

    if s <= x * n {
        println!("0");
    } else {
        let ans = ceil_div(s - n * x, x - 1000);
        println!("{}", ans);
    }

    /*
    S = A+2B+3C+4D
    (S+p) / (N+p) <= X
    S + p <= NX + pX
    (S - NX) <= p(X - 1)
    (S - NX) / (X - 1) <= p
    p = ceil((S - NX) / (X-1))
    */
}
