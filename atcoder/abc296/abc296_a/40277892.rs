fn main() {
    proconio::input! {
        n: usize,
        s: proconio::marker::Chars
    }
    for i in 0..n - 1 {
        let ans = match s[i] {
            'M' => s[i + 1] == 'F',
            'F' => s[i + 1] == 'M',
            _ => unreachable!(),
        };
        if !ans {
            println!("No");
            return;
        }
    }
    println!("Yes");
}
