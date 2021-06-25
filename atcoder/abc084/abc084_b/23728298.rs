use proconio::input;
use regex::Regex;
fn main() {
    input! {
        a: usize, b: usize,
        s: String
    }
    let re_str = format!("^[0-9]{{{}}}-[0-9]{{{}}}$", a, b);
    let re = Regex::new(&re_str).unwrap();

    if re.is_match(&s) {
        println!("Yes");
    } else {
        println!("No");
    }
}
