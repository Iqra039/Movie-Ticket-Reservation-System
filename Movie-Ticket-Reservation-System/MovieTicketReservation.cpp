#include<iostream>
#include<iomanip>
#include<fstream>       //required for file handling
#include<string>        // required for getline to work
#include<cstdlib>      //needed for exit(0)
using namespace std;

string movieTitle[100];                 //an array to store movie titles
string movieGenre[50];                  //an array to store genre
int showTime[100];                      //an array to store the 
int movieCount = 0;                     //array size
int bookedSeats[100] = { 0 };
int totalSeats = 100;
string reservationNames[100][100];      // stores names for each movie
int reservationCount[100] = { 0 };      // tracks how many reservations per movie

//To save movies history to file 
void saveTohistory(string msg) {
	ofstream file("history.txt", ios::app);
	file << msg << endl;
	file.close();
}
// to save a movie whenever it's added
void saveMovieToFile(string title, string genre, int time) {
	ofstream file("movies.txt", ios::app); // append mode
	file << title << "\n" << genre << "\n" << time << "\n";
	file.close();
}
/* -------------Functionto load movies from movies.txt when the program starts------------*/
void loadMovies() {
	ifstream file("movies.txt");
	while (file >> ws && getline(file, movieTitle[movieCount])) {
		getline(file, movieGenre[movieCount]);
		file >> showTime[movieCount];
		file.ignore();
		movieCount++;
	}
	file.close();
}
/*-------------Fuction to Save a new reservation------------------------*/
void saveReservationToFile(string movie, string name) {
	ofstream file("reservations.txt", ios::app);
	file << movie << "\n" << name << "\n";
	file.close();
}
/*--------------Function to load Reservations from reservations.txt------------*/
void loadReservations() {
	ifstream file("reservations.txt");
	string movie, name;
	while (getline(file, movie) && getline(file, name)) {
		for (int i = 0; i < movieCount; i++) {
			if (movie == movieTitle[i]) {
				reservationNames[i][reservationCount[i]] = name;
				reservationCount[i]++;
				bookedSeats[i]++;
				break;
			}
		}
	}
	file.close();
}
/*------------function to Update the file movies.txt when a movie is deleted by the admin -------------*/
void updateMoviesFile() {
	ofstream file("movies.txt", ios::trunc);
	for (int i = 0; i < movieCount; i++) {
		file << movieTitle[i] << "\n" << movieGenre[i] << "\n" << showTime[i] << "\n";
	}
	file.close();
}
/*-------function to update reservations, when a movie is deleted, to remove all reservations for that movie.--------*/
void updateReservationsFile() {
	ofstream file("reservations.txt", ios::trunc);
	for (int i = 0; i < movieCount; i++) {
		for (int j = 0; j < reservationCount[i]; j++) {
			file << movieTitle[i] << "\n" << reservationNames[i][j] << "\n";
		}
	}
	file.close();
}

/*-------------- - function to add New Movie using Pointers--------------------*/
void addMovie(string* titles, string* genres, int* times, int& count) {
	//take movie input from user for Movie Name and store it at index[count]
	cout << "Enter movie title: ";
	getline(cin, titles[count]);

	//Take input from user for Genre and store it at index[count]
	cout << "Enter movie genre: ";
	getline(cin, genres[count]);
	//Take input from user for Movie Showtime and store it at index[count]
	cout << "Enter show time(in pm): ";
	cin >> times[movieCount];
	cin.ignore();
	//saving record to history.txt file
	saveTohistory("Movie added: " + movieTitle[movieCount]);
	saveMovieToFile(titles[count], genres[count], times[movieCount]);
	count++;

	cout << "\nMovie added successfully...\n" << endl;
	system("pause");

}

/*--------------------- A Function that Displays All the Movies-----------------------*/
void viewMovies() {
	cout << "\n========================================================================================\n";
	cout << "| MOVIE ID |        TITLE         |     GENRE     |  SHOWTIME (PM)  | AVAILABLE SEATS |\n";
	cout << "----------------------------------------------------------------------------------------\n";
	for (int i = 0; i < movieCount; i++) {
		int availableSeats = totalSeats - bookedSeats[i];
		/*cout << " | " << setw(10) << i + 1 << " | " << setw(20) << movieTitle[i] << " | " << setw(12) << movieGenre[i] << " | " << setw(10) << showTime[i] << " | " << setw(18) << availableSeats << endl;*/
		cout << "| " << setw(8) << i + 1 << " | " << setw(20) << left << movieTitle[i] << right << " | " << setw(12) << left << movieGenre[i] << right << " | " << setw(15) << showTime[i] << " | " << setw(15) << availableSeats << " |\n";
	}
	cout << "========================================================================================\n";
	system("pause");
}
/*-----------------------------------------------------------------------------------*/

/*--------------Function to Search for a Movie-----------------------*/
void search() {
	int search_choice;   //variable to take choice from user
	string name, genre;  //variables for user input to search movie by name/Genre
	int time;            //variable for user input to search movie by show time
	bool found = false;

	cout << "\nSearch the Movie by \n1. Name: \n2. Genre: \n3. Show time: " << endl;
	cin >> search_choice;
	cin.ignore();
	cout << endl;

	switch (search_choice) {
		//search by Movie Name
	case 1: {
		cout << "Enter The Movie Name: ";
		getline(cin, name);                //taking movie name as input 
		for (int i = 0;i < movieCount;i++) {
			if (name == movieTitle[i]) {      //searching movie name 
				cout << "Yes Movie available at " << showTime[i] << " PM\n" << endl;
				found = true;
				break;
			}
		}

		if (!found) {
			cout << "Sorry! could not find a movie with this name.\n";
		}
		break;

	}
		  //Search by genre
	case 2: {
		cout << "Enter Movie Genre: ";
		getline(cin, genre); //use getline to handle multi-word genres
		for (int i = 0; i < movieCount; i++) {
			if (genre == movieGenre[i]) {
				cout << "The movie " << movieTitle[i] << " is available with this genre at " << showTime[i] << "PM\n" << endl; //searching movie names with this genre
				found = true;
			}
			if (!found)
				cout << "Sorry could not find a movie with this Genre! Please Enter 1 to add this movie.\n" << endl;
		}
	}
		  break;
		  //Search by Showtime
	case 3: {
		cout << "Enter movie show time: ";
		cin >> time;
		found = false;
		for (int i = 0; i < movieCount; i++) {
			if (time == showTime[i]) {
				cout << "Yes the Movie " << movieTitle[i] << " is available for the show time " << time << endl;
				found = true;
			}
		}
		if (!found) {
			cout << "Sorry could not find a movie with this show time\n" << endl;
		}
		break;
	}
	default: {
		cout << "invalid choice! please enter a valid choice \n" << endl;
	}
	}
	system("pause");
}

/*----------------Function to Book tickets------------------*/
void bookTickets() {
	string movieName, yourName;
	bool found = false;

	cout << "Please enter you name for reservation: ";
	getline(cin, yourName);
	cout << "Enter the Movie Name: ";
	getline(cin, movieName);
	cout << endl;
	for (int i = 0;i < movieCount;i++) {
		if (movieName == movieTitle[i]) {                      //checking whether this movie is available
			int availableSeats = totalSeats - bookedSeats[i];  //calculating the available seats
			if (availableSeats > 0) {
				cout << "Ticket booked Successfully under the name " << yourName << endl;
				bookedSeats[i]++;
				reservationNames[i][reservationCount[i]] = yourName;
				reservationCount[i]++;
			}
			else {
				cout << "Sorry, no seats available.\n";
			}
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "Movie not found.\n";
	}
	if (found) {
		saveTohistory("User " + yourName + " booked a ticket for " + movieName);
		saveReservationToFile(movieName, yourName);
	}
	system("pause");
}

/*-------------------Function to View Reservations--------------------*/
void viewReservations() {
	string movieName;
	bool found = false;

	cout << "Enter the movie name to view reservations: "; //asking viewers to enter movie name to view reservations for 
	getline(cin, movieName);

	for (int i = 0; i < movieCount; i++) {
		if (movieTitle[i] == movieName) {  //checking if the movie exists in the list
			found = true;

			if (reservationCount[i] == 0) {   //if zero reseravtions
				cout << "No reservations for this movie yet.\n";
			}
			else {  //if reservations > 0
				cout << "Reservations for " << movieTitle[i] << ":\n";
				for (int j = 0; j < reservationCount[i]; j++) {
					cout << j + 1 << ". " << reservationNames[i][j] << endl;  ///showing reservaton names of all the people who ookes through 2d array
				}
				cout << "Total booked seats: " << reservationCount[i] << endl;
			}
			break;
		}
	}

	if (!found) { //if the movie is not available or does not exist in thh list
		cout << "Movie not found.\n";
	}
	system("pause");
}

/*-----------------Function to Delete a Movie---------------------*/
void deleteMovie() { //function start
	string name;
	bool found = false;

	cout << "Enter the Movie name to delete it from the list: ";  //taking input from the user to delete the movie
	getline(cin, name);

	for (int i = 0; i < movieCount; i++) {
		if (movieTitle[i] == name) {  //checking if the movie is in the list
			found = true;
			for (int j = i;j < movieCount;j++) {
				movieTitle[j] = movieTitle[j + 1];  //shifting the movie data one step up, so that if the movieTitle[0] was to be deleted, movieTitle[1] would take its place
				movieGenre[j] = movieGenre[j + 1];
				showTime[j] = showTime[j + 1];
				bookedSeats[j] = bookedSeats[j + 1];            //increasing te number of booked seats as the movie has been deleted
				reservationCount[j] = reservationCount[j + 1];

				// Shift all reservation names
				for (int k = 0; k < reservationCount[j]; k++) {
					reservationNames[j][k] = reservationNames[j + 1][k];
				}
			}
			movieCount--; //decreasing the movie count as we deleted the movie
			cout << "The movie " << name << " was deleted successfully! " << endl;
			break;
		}
	}
	if (!found) {
		cout << "Could not find the movie \"" << name << "\" in the list.\n";  //error msg if movie not found in the list
	}
	if (found) {
		saveTohistory("Movie deleted: " + name);
		// Update files
		updateMoviesFile();     
		updateReservationsFile();
	}
	system("pause");
}

/*-----------------Function to View History--------------------*/
void viewHistory() {
	ifstream file("history.txt");
	string line;
	cout << "\n--- Action History ---\n";
	while (getline(file, line)) {
		cout << line << endl;
	}
	file.close();
	system("pause");
}
/*--------------------------------------------------------------*/
int main() {
	loadMovies(); // Load previously added movies
	loadReservations();  // Load reservations for those movies
	cout << setw(95) << "Welcome to our Movie Ticket Reservation System" << endl;
	cout << endl;
	int usertype;
	cout << "Select User type \n1.Admin \n2.Customer \n\nEnter your choice: ";
	cin >> usertype;
	cin.ignore();
	cout << endl;
	int choice;
	if (usertype == 1) {
		string pass;
		cout << "Enter Admin Password to continue: ";
		cin >> pass;
		if (pass == "mrbean") {  //if Password is correct it shows menu
			cout << "\nLogging in...\n";

			while (true) { //using a while loop allowing the program to continuously display the menu after each action until the user chooses to exit the program


				cout << "\n\n* * * * * * * * * *" << "--Admin Menu --" << "* * * * * * * * * *" << endl;
				cout << "1. Add New Movie.\n2. View All Movies.\n3. Delete Movie.\n4. View Reservations\n5. View History.\n6. Exit" << endl;
				cout << setw(50) << "* * * * * * * * * * * * * * * * * * * * * * * * * \n\n";
				cout << "Enter Your choice from the Menu above: ";
				cin >> choice;
				cin.ignore();
				cout << endl;
				switch (choice) {
				case 1:
					addMovie(movieTitle, movieGenre, showTime, movieCount);
					break;
				case 2:
					viewMovies();
					break;
				case 3:
					deleteMovie();
					break;
				case 4:
					viewReservations();
					break;
				case 5:
					viewHistory();
					break;
				case 6:
					cout << "\n Logging out...Goodbye Admin! \n" << endl;
					exit(0);
				default:
					cout << "Invalid Option! please choose from the Admin Menu";
					break;
				}
			}

		}
		else {   //if incorrect password show error message and ask for password again
			cout << "\nIncorrect Password!\n";
		}
	}
	else if (usertype == 2) {
		// Customer Menu
		cout << "\nWelcome to Movie Booking System!\n";
		cout << "Browse movies, book your favorite seats, and enjoy the show!\n";
		cout << "Sit back, relax, and let us handle your ticketing.\n" << endl;
		while (true) {
			cout << "\n-------- Customer Menu --------" << endl;
			cout << "1. View All Movies\n2. Search Movie\n3. Book Tickets\n4. Exit\n";
			cout << "-------------------------------\n\n";
			cout << "Enter your choice: ";
			cin >> choice;
			cin.ignore();

			switch (choice) {
			case 1:
				viewMovies();
				break;
			case 2:
				search();
				break;
			case 3:
				bookTickets();
				break;
			case 4:
				cout << "\nThank you for using our Movie Ticket Reservation System!" << endl;
				cout << "Enjoy your movie experience. Goodbye!\n";
				exit(0);
			default:
				cout << "Invalid Option! Please choose from the Customer Menu.\n";
			}
		}
	}
	else {
		cout << "Invalid user type selected. Exiting.\n";
	}

	return 0;
}