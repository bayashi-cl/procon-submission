use petgraph::unionfind::UnionFind;
use proconio::{input, marker::Usize1};
use std::collections::{HashSet, VecDeque};

struct BreadthFirstSearch {
    graph: Vec<Vec<(i32, usize)>>,
}
impl BreadthFirstSearch {
    fn search(&self, start: usize) -> bool {
        let n = self.graph.len();
        let mut cost = vec![i32::max_value(); n];
        cost[start] = 0;
        let mut que = VecDeque::new();
        que.push_back(start);
        while !que.is_empty() {
            let dep = match que.pop_front() {
                Some(n) => n,
                None => panic!("err"),
            };
            for (dist, arr) in &self.graph[dep] {
                if cost[*arr] == i32::max_value() {
                    cost[*arr] = cost[dep] + *dist;
                    que.push_back(*arr);
                } else {
                    if cost[*arr] != cost[dep] + *dist {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

fn main() {
    input! {
        n: usize, m: usize,
    }
    let mut adj: Vec<Vec<(i32, usize)>> = vec![vec![]; n];
    let mut uft = UnionFind::new(n);
    for _ in 0..m {
        input! {
            l: Usize1,
            r: Usize1,
            d: i32,
        }
        uft.union(l, r);
        adj[l].push((d, r));
        adj[r].push((-d, l))
    }
    let mut s: HashSet<usize> = HashSet::new();
    for i in 0..n {
        s.insert(uft.find(i));
    }
    let bfs = BreadthFirstSearch { graph: adj };
    for i in s {
        if bfs.search(i) {
            continue;
        }
        println!("No");
        return;
    }
    println!("Yes");
}
