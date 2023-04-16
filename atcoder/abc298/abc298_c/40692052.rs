use itertools::Itertools;
use proconio::input;
use std::collections::{HashMap, HashSet};

fn main() {
    input! {
        _n: usize,
        q: usize,
    }
    let mut boxes = HashMap::<usize, Vec<usize>>::new();
    let mut cards = HashMap::<usize, HashSet<usize>>::new();

    for _ in 0..q {
        input! {
            t: i32,
        }

        match t {
            1 => {
                input! {
                    i: usize, j: usize,
                }
                boxes.entry(j).or_insert(vec![]).push(i);
                cards.entry(i).or_insert(HashSet::new()).insert(j);
            }
            2 => {
                input! {
                    i: usize,
                }
                let ans = boxes.entry(i).or_default();
                ans.sort();
                println!("{}", ans.iter().join(" ").to_string());
            }
            3 => {
                input! {
                    i: usize,
                }
                let mut ans = cards.entry(i).or_default().iter().collect::<Vec<_>>();
                ans.sort();
                println!("{}", ans.iter().join(" ").to_string());
            }
            _ => unreachable!(),
        }
    }
}
