use proconio::input;

#[derive(Debug)]
struct Point {
    x: i64,
    y: i64,
}

impl Point {
    fn new(x: i64, y: i64) -> Self {
        Point { x, y }
    }
}

#[derive(PartialEq, Eq)]
enum Turn {
    Back,
    Right,
    Middle,
    Left,
    Front,
}
fn det(a: &Point, b: &Point) -> i64 {
    return a.x * b.y - a.y * b.x;
}
fn dot(a: &Point, b: &Point) -> i64 {
    return a.x * b.x + a.y * b.y;
}

fn isp(a: &Point, b: &Point, c: &Point) -> Turn {
    // a -> b -> c
    let ab = Point::new(b.x - a.x, b.y - a.y);
    let ac = Point::new(c.x - a.x, c.y - a.y);
    let d = det(&ab, &ac);
    if d < 0 {
        return Turn::Right;
    } else if d > 0 {
        return Turn::Left;
    } else {
        let bc = Point::new(c.x - b.x, c.y - b.y);
        let ba = Point::new(a.x - b.x, a.y - b.y);
        if dot(&ab, &bc) > 0 {
            return Turn::Front;
        } else if dot(&ba, &ac) > 0 {
            return Turn::Back;
        } else {
            return Turn::Middle;
        }
    }
}

fn main() {
    input! {
        n: usize,
        xy: [(i64, i64); n],
        q: usize,
        ab: [(i64, i64); q]
    }

    let mut poly = Vec::new();
    for (x, y) in &xy {
        poly.push(Point::new(*x, *y));
    }
    let mut query = Vec::new();
    for (a, b) in &ab {
        query.push(Point::new(*a, *b));
    }

    let poly = poly;
    let query = query;
    for p in &query {
        if isp(&poly[0], &poly[1], p) == Turn::Middle
            || isp(&poly[0], &poly[n - 1], p) == Turn::Middle
        {
            println!("ON");
            continue;
        }

        let mut r = n as i32;
        let mut l = 0 as i32;

        while (r - l).abs() > 1 {
            let mid = (l + r) / 2;
            let pred = {
                if mid < 1 {
                    true
                } else if mid == n as i32 {
                    false
                } else {
                    isp(&poly[0], &poly[mid as usize], &p) == Turn::Left
                }
            };

            if pred {
                l = mid;
            } else {
                r = mid;
            }
        }

        let i = l as usize;
        if i == 0 || i == n - 1 {
            println!("OUT");
        } else {
            // poly[0];
            // poly[i];
            // poly[i + 1];
            let t0 = isp(&poly[0], &poly[i], &p);
            let t1 = isp(&poly[i], &poly[i + 1], &p);
            let t2 = isp(&poly[i + 1], &poly[0], &p);

            if t1 == Turn::Middle {
                println!("ON");
            } else if t0 == Turn::Middle || t2 == Turn::Middle {
                println!("IN");
            } else if t0 == Turn::Left && t1 == Turn::Left && t2 == Turn::Left {
                println!("IN");
            } else {
                println!("OUT");
            }
        }
    }
}
