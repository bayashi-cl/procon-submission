fn main() {
    proconio::input! {mut a: i64, mut b: i64, mut c: i64, mut d: i64}
    if b < 0 {
        a = -a;
        b = -b;
    }
    if d < 0 {
        c = -c;
        d = -d;
    }

    let l = a * d;
    let r = c * b;

    if l < r {
        println!("<");
    } else if l > r {
        println!(">");
    } else {
        println!("=");
    }
}
