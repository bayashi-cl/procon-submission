use proconio::{input, marker::Usize1};
fn main() {
    input! {
        n: usize,
        m: usize,
        ab: [(Usize1, Usize1); m]
    }

    let mut graph = vec![Vec::new(); n];
    let mut deg = vec![0; n];
    for (a, b) in &ab {
        deg[*b] += 1;
        graph[*a].push(*b);
    }
    let mut st = Vec::new();
    for i in 0..n {
        if deg[i] == 0 {
            st.push(i);
        }
    }
    let mut topo = Vec::new();
    while !st.is_empty() {
        let top = st.pop().unwrap();
        topo.push(top);
        for nxt in &graph[top] {
            deg[*nxt] -= 1;
            if deg[*nxt] == 0 {
                st.push(*nxt);
            }
        }
    }
    let ans = if topo.len() == n { "Yes" } else { "No" };
    println!("{}", ans);
}
