use proconio::input;
fn main() {
    input! {
        a:i32,
        b:i32
    }

    if a * b % 2 == 1 {
        println!("Odd");
    } else {
        println!("Even");
    }
}
