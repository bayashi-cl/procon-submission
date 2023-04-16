use proconio::input;

fn main() {
    input! {
        n: usize,
        mut a: [[i32; n]; n],
        b: [[i32; n]; n],
    }

    for _ in 0..4 {
        let mut rot_a = vec![vec![0; n]; n];
        for i in 0..n {
            for j in 0..n {
                rot_a[i][j] = a[n - j - 1][i];
            }
        }
        a = rot_a;

        let mut flg = true;
        for i in 0..n {
            for j in 0..n {
                if a[i][j] == 1 && b[i][j] != 1 {
                    flg = false;
                }
            }
        }
        if flg {
            println!("Yes");
            return;
        }
    }
    println!("No");
}
