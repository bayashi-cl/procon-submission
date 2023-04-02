use proconio::marker::Usize1;

struct FenwickTree {
    data: Vec<i64>,
    n: usize,
}

impl FenwickTree {
    fn new(n: usize) -> Self {
        FenwickTree {
            data: vec![0_i64; n + 1],
            n,
        }
    }

    fn prefix_fold(&self, r: usize) -> i64 {
        let mut result = 0_i64;
        let mut i = r as i64;
        while i > 0 {
            result += self.data[i as usize];
            i -= i & -i;
        }
        return result;
    }
    fn fold(&self, l: usize, r: usize) -> i64 {
        return self.prefix_fold(r) - self.prefix_fold(l);
    }
    fn point_append(&mut self, mut i: usize, val: i64) {
        i += 1;
        while i <= self.n {
            self.data[i] += val;
            i += i & i.wrapping_neg();
        }
    }
}

fn inversion_number(v: &Vec<usize>) -> i64 {
    let n = v.len();
    let mut ft = FenwickTree::new(n);
    let mut result = 0;
    for vi in v {
        result += ft.fold(*vi + 1, n);
        ft.point_append(*vi, 1_i64);
    }
    return result;
}

fn main() {
    proconio::input! {
        n: usize,
        mut a: [Usize1; n],
        mut b: [Usize1; n]
    }

    let inv_a = inversion_number(&a);
    let inv_b = inversion_number(&b);

    a.sort();
    b.sort();

    for i in 0..n {
        if a[i] != b[i] {
            println!("No");
            return;
        }
    }
    for i in 0..n - 1 {
        if a[i] == a[i + 1] {
            println!("Yes");
            return;
        }
    }

    if inv_a % 2 == inv_b % 2 {
        println!("Yes");
    } else {
        println!("No");
    }
}
