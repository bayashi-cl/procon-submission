use proconio::input;

fn main() {
    input! {
        n: usize,
        station: [(i32, i32, i32); n-1]
    }
    for i in 0..n {
        let mut time = 0;
        for j in i..(n - 1) {
            let (c, s, f) = station[j];
            if time <= s {
                time = s + c;
            } else {
                let next: i32 = if time % f == 0 {
                    time
                } else {
                    (time / f + 1) * f
                };
                time = next + c;
            }
        }
        println!("{}", time);
    }
}
