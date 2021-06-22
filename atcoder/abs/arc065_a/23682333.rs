use proconio::input;

fn main() {
    input! {s:String};
    let pat: Vec<Vec<char>> = ["dream", "dreamer", "erase", "eraser"]
        .iter()
        .map(|s| s.chars().rev().collect())
        .collect();
    let s: Vec<char> = s.chars().rev().collect();
    let mut s = &s[..];
    let mut ans = true;

    while s.len() > 0 {
        let matched = pat.iter().find(|&p| s.starts_with(p));
        if let Some(p) = matched {
            s = &s[p.len()..];
        } else {
            ans = false;
            break;
        }
    }
    println!("{}", if ans { "YES" } else { "NO" })
}
