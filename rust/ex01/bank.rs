use std::collections::HashMap;
use std::fmt::{Display, Debug};

pub struct Bank<T, U> {
	banker: String,
	vault: HashMap<String, T>,
	lock_box: HashMap<String, Vec<U>>,
	min_deposit: T
}

impl<T: PartialOrd + Display, U: Debug> Bank<T, U> {
	pub fn new(banker: String, min_deposit: T) -> Self {
		Self { 
			banker, 
			vault: Vec::new(), 
			lock_box: HashMap::new(),
			min_deposit
		}
	}
	
	pub fn greeting(&self) {
		println!("hi welcome to my bank my name is {}", self.banker);
	}

	pub fn banker(&self) -> &String {
		&self.banker
	}
	
	// 	You will take the file and change the struct to match the above example. You will need to update your deposit(&mut self, customer: &str, amount: T) function to utilize the HashMap functionality to save a running sum for whomever is depositing. The customer’s name will be the key and you will add the amount to the value. The parameters will stay the same, it will check if the customer is depositing at least min_deposit. If so that it check if the customer has an account, by checking the HashMap for the key corresponding to the name, then it updates the value with the new added deposit.
	// You will also need to update your impl block. I will not give you this signature as it could be different depending on what Traits you deem necesarry to accomplish the goal. There are many traits in the std library of rust, and you can use many different combinatiosn to accomplish this task. 
	// Additonally implement the following functions.
	pub fn deposit(&mut self, customer: &str, amount: T) {
		if amount < self.min_deposit {
			println!("{} is less than the minimum deposit of {}", amount, self.min_deposit);
			return;
		}
		if self.vault.contains_key(customer) {
			let current_amount = self.vault.get(customer).unwrap();
			self.vault.insert(customer.to_string(), current_amount + amount);
		} else {
			self.vault.insert(customer.to_string(), amount);
		}
	}

	pub fn deposit_lock_box(&mut self, customer: &str, item: U) {
		let l_box = self.lock_box.entry(customer.to_string()).or_insert(Vec::new());
		(*l_box).push(item);
		println!("{customer}, your item is now locked away\n - {}", self.banker);
		for (cust, loot) in &self.lock_box {
			println!("in box {:?}", loot);
		}
	}

	// This will take in a &str that correlates to a customer’s name and is used as the key for the vault HashMap.  The amount is how much they wish to withdraw from their account. You will use the name to check if they have an account and if so how much money is in it. If they do not have an account, do not add them to the HashMap vault.
	// If they have money return the value taken from their account and update their account. If they do not have enough return 0. (Hint: T::default()).
	pub fn withdrawal(&mut self, customer: &str, amount: T) -> T {
		if self.vault.contains_key(customer) {
			let current_amount = self.vault.get(customer).unwrap();
			if current_amount < &amount {
				println!("{} does not have enough money to withdraw {}", customer, amount);
				return T::default();
			}
			self.vault.insert(customer.to_string(), current_amount - amount);
			return amount;
		}
		println!("{} does not have an account", customer);
		return T::default();
	}

	// This will take in a &str that correlates to a customer’s name and is used as the key for the vault HashMap. The item will be of type U (it will be tested with Strings). If an item matching this is in the lock_box’s HashMap Vector value, then remove it from there and return the value. If they do not have an account, do not add them to the HashMap lock_box.
	pub fn retrieve(&mut self, customer: &str, item: U) -> Option<U> {
		if self.lock_box.contains_key(customer) {
			let l_box = self.lock_box.get_mut(customer).unwrap();
			let index = l_box.iter().position(|x| *x == item);
			if let Some(index) = index {
				return l_box.remove(index);
			}
		}
		return None;
	}
}

