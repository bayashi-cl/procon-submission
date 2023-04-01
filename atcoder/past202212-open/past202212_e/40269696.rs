fn main() {
    proconio::input! {
        s: String
    }
    let mut cnt = 0;
    for c in s.chars() {
        match c {
            '(' => cnt += 1,
            ')' => cnt -= 1,
            _ => unreachable!(),
        }
        if cnt < 0 {
            println!("No");
            return;
        }
    }
    println!("{}", if cnt == 0 { "Yes" } else { "No" });
}
