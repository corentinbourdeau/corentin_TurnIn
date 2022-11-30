use std::io;
use rand::random;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_fahrenheit_celsius_converter() {
        assert_eq!(fahrenheit_celsius_converter(52, true), 11.111111);
        assert_eq!(fahrenheit_celsius_converter(0, false), 32.0);
        assert_eq!(fahrenheit_celsius_converter(32, true), 0.0);
    }
    #[test]
    fn test_dice_roll() {
        assert!(dice_roll(6) >= 1 && dice_roll(6) <= 6);
        assert!(dice_roll(8) >= 1 && dice_roll(8) <= 8);
        assert!(dice_roll(10) >= 1 && dice_roll(10) <= 10);
        assert!(dice_roll(15) >= 1 && dice_roll(15) <= 15);
    }

    #[test]
    fn test_multi_string() {
        assert_eq!(
            multi_string("../".to_owned()),
            ["../", "../ONE", "../TWO", "../THREE"]
        );
        assert_eq!(
            multi_string("fish".to_owned()),
            ["fish", "fishONE", "fishTWO", "fishTHREE"]
        );
    }

    #[test]
    fn test_add_vowels() {
        let mut s = "bok fod".to_owned();
        add_vowels(&mut s);
        assert_eq!(s, "book food");
        let mut s = "papero".to_owned();
        add_vowels(&mut s);
        assert_eq!(s, "paapeeroo");
        let mut s = "BOOK".to_owned();
        add_vowels(&mut s);
        assert_eq!(s, "BOOOOK");
        let mut s = "Over".to_owned();
        add_vowels(&mut s);
        assert_eq!(s, "OOveer");
    }

    #[test]
    fn test_ghost_name_generator() {
        let mut s = "John".to_owned();
        ghost_name_generator(&mut s);
        assert_eq!(s, "Josnoo");
        let mut s = "Steven".to_owned();
        ghost_name_generator(&mut s);
        assert_eq!(s, "Stebooveboonoo");
        let mut s = "Tim".to_owned();
        ghost_name_generator(&mut s);
        assert_eq!(s, "Tim");
        let mut s = "Henry".to_owned();
        ghost_name_generator(&mut s);
        assert_eq!(s, "Seboonooreeeyoo");
    }
}

pub fn fahrenheit_celsius_converter(temperature: i32, f2c: bool) -> f32 {
    if f2c {
        (temperature as f32 - 32.0) * 5.0 / 9.0
    } else {
        (temperature as f32 * 9.0 / 5.0) + 32.0
    }
}

pub fn dice_roll(sides: u8) -> u8 {
    random::<u8>() % sides + 1
}

pub fn multi_string(s: String) -> [String; 4] {
    let mut s1 = s.clone();
    let mut s2 = s.clone();
    let mut s3 = s.clone();
    s1.push_str("ONE");
    s2.push_str("TWO");
    s3.push_str("THREE");
    [s, s1, s2, s3]
}

// Takes in a mutable reference to a String and updates the actual String
// itself. Any vowels in the String must duplicated (not counting ‘y’).
pub fn add_vowels(s: &mut String) {
    let mut s2 = String::new();
    for c in s.chars() {
        if c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
            || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' {
            s2.push(c);
        }
        s2.push(c);
    }
    *s = s2;
}

// Takes in a String and slices it into 2 sub-strings. Each of these substrings are then printed num amount of times.
pub fn echo_split(whole: String, num: u32) {
    let (first, second);
    if num%2 == 1 {
        (first, second) = whole.split_at(whole.len() / 2);
    } else {
        (first, second) = whole.split_at((whole.len() + 1) / 2);
    }
    for _ in 0..num {
        print!("{}", first);
    }
    print!(" ");
    for _ in 0..num {
        print!("{}", second);
    }
    println!("");
}

pub fn input_number(high: u32) -> Option<u32> {
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let input: u32 = match input.trim().parse() {
        Ok(num) => num,
        Err(_) => return None,
    };
    if input >= high {
        return None;
    }
    Some(input)
}

#[derive(Debug)]
pub enum Card {
    Diamond(String),
    Club(String),
    Heart(String),
    Spade(String)
}
pub fn draw_card() -> Card {
    let suit = random::<u8>() % 4;
    let face = random::<u8>() % 13;
    let face = match face {
        0 => "2".to_owned(),
        1 => "3".to_owned(),
        2 => "4".to_owned(),
        3 => "5".to_owned(),
        4 => "6".to_owned(),
        5 => "7".to_owned(),
        6 => "8".to_owned(),
        7 => "9".to_owned(),
        8 => "10".to_owned(),
        9 => "Jack".to_owned(),
        10 => "Queen".to_owned(),
        11 => "King".to_owned(),
        12 => "Ace".to_owned(),
        _ => "2".to_owned(),
    };
    match suit {
        0 => Card::Diamond(face),
        1 => Card::Club(face),
        2 => Card::Heart(face),
        3 => Card::Spade(face),
        _ => Card::Diamond(face),
    }
}

// Takes in input from the user. It takes 2 Strings from the user and parses
// them into u8s. Those u8s are then returned as a tuple. This Tuple represents
// coordinates in a square field of with sides the length of side. The
// coordinates of the square are from 0 – size. So if the user inputs a number
// equal to or greater than size it is considered out of bounds.
// You must handle all errors and edge cases that might occur. If the user
// inputs something that is not a number or the number they input is out of
// bounds. The function continues until the user has successfully inputs 2
// numbers or there is an error with input, in which case an invalid tuple (size,
// size) is passed back.
pub fn input_coord(size: u8) -> (u8, u8) {
    println!("enter coordinates for {} x {}:", size, size);
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let x: u8 = match input.trim().parse() {
        Ok(num) => if num >= size {
            println!("{} is out of bounds on a boards of size {}", num, size);
            return input_coord(size)
        } else { num },
        Err(_) => {
            println!("\"{}\" is not a number, error: invalid digit found in string", input.trim());
            return input_coord(size)
        }
    };
    println!("enter coordinates for {} x {}:", size, size);
    let mut input = String::new();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    let y: u8 = match input.trim().parse() {
        Ok(num) => if num >= size {
            println!("{} is out of bounds on a boards of size {}", num, size);
            return input_coord(size)
        } else { num },
        Err(_) => {
            println!("\"{}\" is not a number, error: invalid digit found in string", input.trim());
            return input_coord(size)
        }
    };
    (x,y)
}

// This function asks the user for input. The input corresponds with a type
// of word (adjective, noun, past tense verb etc). The user provides the input,
// the function saves the input and once it receives all the input it prints out
// a string using the user provided strings. You must have at least 5 words of
// input in the madlib, but otherwise you can do it however you like.
pub fn madlib() {
    let mut adj = String::new();
    let mut noun = String::new();
    let mut verb = String::new();
    let mut adv = String::new();
    let mut adj2 = String::new();
    println!("Enter an adjective:");
    io::stdin().read_line(&mut adj).expect("Failed to read line");
    println!("Enter a noun:");
    io::stdin().read_line(&mut noun).expect("Failed to read line");
    println!("Enter a verb:");
    io::stdin().read_line(&mut verb).expect("Failed to read line");
    println!("Enter an adverb:");
    io::stdin().read_line(&mut adv).expect("Failed to read line");
    println!("Enter an adjective:");
    io::stdin().read_line(&mut adj2).expect("Failed to read line");
    println!("{} {} {} {} {}", adj.trim(), noun.trim(), verb.trim(), adv.trim(), adj2.trim());
}

// to find out your ghost name:
// Use your first name:
// a - add “t” after it
// e - add “boo” after it
// h - becomes “s”
// n - add “oo” after it
// r - add “eee” after it
// y - add “oo” after it
// that’s it that’s your ghost name
// - @nathanwpyle
// This function will take in a mutable reference to a String and it will
// convert that String to the proper Ghost Name, using the above rules.
pub fn ghost_name_generator(s: &mut String) {
    let mut new = String::new();
    for c in s.chars() {
        match c {
            'a' => new.push_str("t"),
            'e' => new.push_str("boo"),
            'h' => new.push_str("s"),
            'n' => new.push_str("oo"),
            'r' => new.push_str("eee"),
            'y' => new.push_str("oo"),
            _ => new.push(c),
        }
    }
    *s = new;
}

// This function will print out a 3x3 box, that could repressent a game of
// tic-tac-toe at any given state. It takes 2 arrays of tuples. The tuples each
// contain 2 u8s which coordinate to positions in the box you will print out. If
// there exists a space on the board that is not covered by a tuple it will print
// out a ‘-’. If a tuple in exes occurs within the board print out ‘X’. If a
// tuple in oes occurs on the board, print out ‘O’. (4, 4) represents something
// out of bounds.
pub fn print_board(exes:[(u8, u8);5], oes: [(u8, u8);5]) {
    let mut board = [['-'; 3]; 3];
    for (x, y) in exes.iter() {
        if *x < 3 && *y < 3 {
            board[*x as usize][*y as usize] = 'X';
        }
    }
    for (x, y) in oes.iter() {
        if *x < 3 && *y < 3 {
            board[*x as usize][*y as usize] = 'O';
        }
    }
    for row in board.iter() {
        for c in row.iter() {
            print!("{} ", c);
        }
        println!();
    }
}

// Implements logic for playing a game of tic-tac-toe. The print_board and
// coord_input functions will help a lot. The game will keeep track of whose turn
// it is and ask for input. It will save that input in an array and use it to
// draw the board. Once a “spot” on the board has been used, then it cannot be
// used again.
// The game will calculate whether or not either player has gotten 3 in a
// row and declare a winner when that person does. If the board is filled and
// there is no winner, then a time is declared.
// TIC-TAC-TOE
// -----
// - - -
// - - -
// - - -
// -----
// X turn
// enter coordinate for 3 x 3:
// 1
// enter coordinate for 3 x 3:
// 1
// -----
// - - -
// - X -
// - - -
// -----
// O turn
// enter coordinate for 3 x 3:
// 0
// enter coordinate for 3 x 3:
// 1
// -----
// - - -
// O X -
// - - -
// -----
// X turn
// enter coordinate for 3 x 3:
// 0
// enter coordinate for 3 x 3:
// 0
// -----
// - - -
// O X -
// X - -
// -----
// O turn
// enter coordinate for 3 x 3:
// 2
// enter coordinate for 3 x 3:
// 1
// -----
pub fn tic_tac_toe() {
}

// This function emulates a classic dice game. A man with no seamanship
// skills, wishes to go out to see and collect treasure. To do this he needs 3
// things, a ship, a captain, and a crew. To play the game you need 5 dice. Each
// time you roll the dice you must take one into your hand, you may take more
// than 1 if you’d like. The game ends when you have taken all 5 dice into your
// hand.
// To score in the game you need 3 things, a ship(4), a captain(5), and a
// crew(6). Each of these coresponds with a value on a 6 sided die. So if you
// don’t have a 4, 5 and a 6 in your hand you get 0 points. If you do have a
// ship, captain and crew then the remaining 2 dice are your points.
// Within the function you generate random dice rolls (with dice_roll()) and
// store them and print them out to screen. The user then gives input(with
// input_number()) as to what they want to take into their hand. If the input
// given is not a number we assume they are ready to roll again. But every time
// they roll they must take at least one die. Once their hand is full you
// calculate the points and print them out.
pub fn ship_captain_crew() {
    let mut hand = [0; 5];
    let mut dice = [0; 5];
    let mut points = 0;
    let mut ship = false;
    let mut captain = false;
    let mut crew = false;
    let mut roll = 0;
    while roll < 5 {
        for i in 0..5 {
            dice[i] = dice_roll(4);
        }
        println!("Dice: {:?}", dice);
        println!("Hand: {:?}", hand);
        println!("Points: {}", points);
        println!("Roll: {}", roll);
        println!("Ship: {}", ship);
        println!("Captain: {}", captain);
        println!("Crew: {}", crew);
        println!("Enter a number to take into your hand:");
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let input: u32 = match input.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        if input > 5 {
            continue;
        }
        hand[roll] = dice[input as usize];
        roll += 1;
        if hand[0] == 4 {
            ship = true;
        }
        if hand[1] == 5 {
            captain = true;
        }
        if hand[2] == 6 {
            crew = true;
        }
        if ship && captain && crew {
            points = hand[3] + hand[4];
        }
    }
    println!("Dice: {:?}", dice);
    println!("Hand: {:?}", hand);
    println!("Points: {}", points);
    println!("Roll: {}", roll);
    println!("Ship: {}", ship);
    println!("Captain: {}", captain);
    println!("Crew: {}", crew);
}