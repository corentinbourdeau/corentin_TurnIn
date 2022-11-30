use std::io;

fn main() {
    println!("Hello, world!");
// Variable :
    // Ne pas faire:
        // let x = 5;
        // x +=1;
    // Good:
    let mut y = 5;
    println!("y = {}", y);
    y +=1;
    println!("y = {}", y);
// Const
    const BABY:u32 = 5 * 9999;
    println!("BABY = {}", BABY);
// Scopes
    let z = 3;
    {
        let z = z+1;
        println!("z = {}", z);
    }
    println!("z = {}", z);
// Scalar
    // integers
        // unsigned (u8, u16, u32, u64, u128, usize)
        // signed (i8, i16, i32, i64, i128, isize)
        // u8 = -128 to 127
        // i8 = 0 to 255
    // floating
        // f32, f64
    // boolean
        // bool
    // character
        // char
                    // let mut i:u8 = 255;
                    // if rond {
                    //     i += 1;
                    // }
                    // println!("i = {}", i);
// Compound
    // Tuple
    let tup: (i32, f64, u8) = (500, 6.4, 1);
    let (_x, _y, _z) = tup;
    println!("The value of y is: {}", _y);
    println!("The value of z is: {}", tup.2);
    // Array
    let a = [1, 2, 3, 4, 5];
    let first = a[0];
    let second = a[1];
    println!("The value of first is: {}", first);
    println!("The value of second is: {}", second);
    // let b = [3; 5];  == let b = [3, 3, 3, 3, 3];
    let c:[u8; 3] = [0;3];
    println!("The value of c is: {}", c[0]);
// String
    let mut s = String::from("Hello");
    s.push_str(", world!");
    println!("{}", s);
    let res = io::stdin().read_line(&mut s).expect("Failed to read line");
    println!("{}", s);
    println!("res = {}", res);
// Enum
    // enum Fruit {
    //     Banana(String),
    //     Apple(u8),
    // }
    // enum Option <T> {
    //     Some(T),
    //     None,
    // }
    // enum Result <Success, Error> {
    //     Ok(Success),
    //     Err(Error),
    // }
// Condition
    // Match
    let num:u8 = 10;
    match num {
        1 => println!("One"),
        2 => println!("Two"),
        3 => println!("Three"),
        4 => println!("Four"),
        5 => println!("Five"),
        6 => println!("Six"),
        7 => println!("Seven"),
        8 => println!("Eight"),
        9 => println!("Nine"),
        10 => println!("Ten"),
        _ => println!("Other"),
    }
    let q = "hi".to_string();
    let c = q.chars().next();
    if let Some(_l) = c {
        println!("I");
    } else {
        println!("Not I");
    }
// loop
    let mut i = 0;
    loop {
        if i == 10 {
            break;
        }
        println!("i = {}", i);
        i += 1;
    }
    for _j in 0..10 {
        println!("j = {}", i);
    }
    // {
    //     s1 = "to".to_string();
    //     s2 = s1.clone();
    //     println!("s1 = {}", s1);
    // }
    mut ref s1 = "to".to_string();
    let s2 = s1.clone();
    println!("s1 = {}", s1);
    println!("s2 = {}", s2);
// Slice
    a = [1, 2, 3, 4, 5];
    let slice = &a[1..3];
    println!("slice = {}", slice[0]);
    // input.parse::<u8>()
    // rand::<u8>()
}