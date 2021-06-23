use proconio::{input, marker::Usize1};
use std::collections::VecDeque;

struct BreadthFirstSearch {
    graph: Vec<Vec<(i32, usize)>>,
    cost: Vec<i32>,
}
impl BreadthFirstSearch {
    pub fn new(graph: Vec<Vec<(i32, usize)>>) -> Self {
        let n = graph.len();
        BreadthFirstSearch {
            graph,
            cost: vec![i32::max_value(); n],
        }
    }
    fn search(&mut self, start: usize) -> bool {
        self.cost[start] = 0;
        let mut que = VecDeque::new();
        que.push_back(start);
        while !que.is_empty() {
            let dep = match que.pop_front() {
                Some(n) => n,
                None => panic!("err"),
            };
            for (dist, arr) in &self.graph[dep] {
                if self.cost[*arr] == i32::max_value() {
                    self.cost[*arr] = self.cost[dep] + *dist;
                    que.push_back(*arr);
                } else {
                    if self.cost[*arr] != self.cost[dep] + *dist {
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
    for _ in 0..m {
        input! {
            l: Usize1,
            r: Usize1,
            d: i32,
        }
        adj[l].push((d, r));
        adj[r].push((-d, l))
    }

    let mut bfs = BreadthFirstSearch::new(adj);
    for i in 0..n {
        if bfs.cost[i] != i32::max_value() {
            continue;
        }
        if bfs.search(i) {
            continue;
        }
        println!("No");
        return;
    }
    println!("Yes");
}
