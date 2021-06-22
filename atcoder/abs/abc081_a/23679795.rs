use proconio::input;
fn main() {
    input! {
        s:String
    }
    let mut cnt = 0;
    for i in s.as_str().chars() {
        if i == '1' {
            cnt += 1;
        }
    }
    println!("{}", cnt);
}
