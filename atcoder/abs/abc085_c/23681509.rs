use proconio::input;

fn main() {
    input! {n:i32, y:i32};
    'outer: for i in 0..=n {
        if i * 10000 > y {
            break;
        }
        for j in 0..=(n - i) {
            let re = y - (i * 10000 + j * 5000);
            if re < 0 {
                continue 'outer;
            } else if re == (n - i - j) * 1000 {
                println!("{} {} {}", i, j, n - i - j);
                return;
            }
        }
    }
    println!("-1 -1 -1");
}
