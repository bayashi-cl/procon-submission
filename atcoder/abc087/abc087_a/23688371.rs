use proconio::input;

fn main() {
    input! {
        x: i32,
        a: i32,
        b: i32,
    }
    print!("{}", (x - a) % b);
}
