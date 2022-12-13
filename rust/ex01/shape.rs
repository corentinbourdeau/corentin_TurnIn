// In this file you will implement several traits and structs. The central theme will be about displaying shapes of various sizes on the command line, there will be 3 shapes, a Rectangle a Triangle and a Square. They will all implement the trait Display and the custom trait TwoD. You will then implement another trait Vec2D that is a blanket implementation of TwoD, this adds the functionality of creating a 2D vector from the shape. The will be given the signatures for the implementations and structs below.

pub trait TwoD {

    /*This function retuns a formatted String that when printed out displays their shape printed out with the sprite char.*/
	fn draw(&self) -> String {
        String::from("Not Implemented")
    }

    /*This functions reutrns the calculated center of the Shape calculated via the implementer’s width and height parameters*/
	fn mid_point(&self) -> (i32, i32) {
        (0, 0)
    }

    /*This function acts as a getter for the implemnter’s height member variable*/
	fn height(&self) -> u32 {
        0
    }

}

pub struct Rect {
	width: u32,
	height: u32,
	sprite: char
}

impl Rect {
	pub fn new(width: u32, height: u32, sprite: char) -> Self {}
}

impl TwoD for Rect {

    /*This function retuns a formatted String that when printed out displays their shape printed out with the sprite char.*/
	fn draw(&self) -> String {
        let mut output = String::new();
        for _ in 0..self.height {
            for _ in 0..self.width {
                output.push(self.sprite);
            }
            output.push('\n');
        }
        output
    }

    /*This functions reutrns the calculated center of the Shape calculated via the implementer’s width and height parameters*/
	fn mid_point(&self) -> (i32, i32) {
        (self.width as i32 / 2, self.height as i32 / 2)
    }

    /*This function acts as a getter for the implemnter’s height member variable*/
	fn height(&self) -> u32 {
        self.height
    }

}
impl Display for Rect {
	fn fmt(&self, f: &mut Formatter<'_>) -> Result {
        write!(f, "{}", self.draw())
    }
}

