// You will extend your mad lib functionality from the previous day, this time designing a struct to hold a variety of different mad libs. You will be provided an impl that your code should adhere to. You will design your own struct for holding the data.
pub struct MadLib {
    pub name: String,
    pub adjective: String,
    pub verb: String,
    pub noun: String,
    pub adverb: String
}

impl MadLib {
    // *instaniates a new MadLib instance, ready to be filled with content.*/
	pub fn new() -> Self {
        name: String::new(),
        adjective: String::new(),
        verb: String::new(),
        noun: String::new(),
        adverb: String::new()
    }

	/*This function takes in to Optional parameters. The first story corresponds to parts of the MadLib that are static, the framework of the story. The Optional variable prompt corresponds to what type of word the user will be prompted to fill at the end of the story &str.*/
	pub fn add_content(&mut self, story: Option<&str>. prompt: Option<&str>) {
        let mut story = story.unwrap_or("Once upon a time, there was a {adjective} {noun} that {verb} {adverb}.");
        let mut prompt = prompt.unwrap_or("Please enter a {noun}.");
        let mut story = story.replace("{adjective}", &self.adjective);
        let mut story = story.replace("{noun}", &self.noun);
        let mut story = story.replace("{verb}", &self.verb);
        let mut story = story.replace("{adverb}", &self.adverb);
        let mut prompt = prompt.replace("{adjective}", "adjective");
        let mut prompt = prompt.replace("{noun}", "noun");
        let mut prompt = prompt.replace("{verb}", "verb");
        let mut prompt = prompt.replace("{adverb}", "adverb");
        println!("{}", story);
        println!("{}", prompt);
    }

    /*This begins the user interaction. The MadLib struct will read out the prompts it has stored from add_content and take in user input and store it within its memory. If the struct has no prompts it does nothing.*/
	pub fn prompt(&mut self) {
        let mut input = String::new();
        if self.adjective == "" {
            println!("Please enter an adjective.");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            self.adjective = input;
        }
        if self.noun == "" {
            println!("Please enter a noun.");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            self.noun = input;
        }
        if self.verb == "" {
            println!("Please enter a verb.");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            self.verb = input;
        }
        if self.adverb == "" {
            println!("Please enter an adverb.");
            io::stdin().read_line(&mut input).expect("Failed to read line");
            self.adverb = input;
        }
    }
    

    /*This function prints out the Strings stored from add_content() as followed by the Strings collected from prompt(), because add content has Options for parameters, the MadLib should be ablle to handle all possible values. If there is nothing stored in the struct it does nothing.*/
	pub fn read(&self) {
        let mut story = "Once upon a time, there was a {adjective} {noun} that {verb} {adverb}.";
        let mut story = story.replace("{adjective}", &self.adjective);
        let mut story = story.replace("{noun}", &self.noun);
        let mut story = story.replace("{verb}", &self.verb);
        let mut story = story.replace("{adverb}", &self.adverb);
        println!("{}", story);
    }

}
