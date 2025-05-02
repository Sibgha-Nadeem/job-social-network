#include <iostream>
#include <fstream>
using namespace std;
class Person
{
protected:
    char* name;
    int user_Id;
public:
    Person()
    {
        user_Id = 0;
        name = nullptr;
    }
    void setid(int i)
    {
        user_Id = i;

    }
    int gettheid()
    {
        return  user_Id;
    }
    ~Person()
    {
        delete[]name;
        name = nullptr;

    }
};
class Education {
protected:
    int total_users;
    char** education;
    char** institute;
    int size1 = 100;
public:
    Education() {
        total_users = 0;
        education = nullptr;
        institute = nullptr;

    }

    void get_education(ifstream& file) {
        int file_total_users;
        file >> file_total_users;
        education = new char* [file_total_users];
        for (int i = 0; i < file_total_users; i++) {
            education[i] = new char[size1];
            file >> education[i];
        }
        total_users = file_total_users;
    }

    void get_institute(ifstream& file) {
        int file_total_users;
        file >> file_total_users;
        int size = 200;
        institute = new char* [file_total_users];
        for (int i = 0; i < file_total_users; i++) {
            institute[i] = new char[size];
            char c;
            int j = 0;
            file.get(c);
            if (c == '-') {
                file.get(c);
            }
            while (file.get(c) && c != '-') {
                institute[i][j++] = c;
            }
            institute[i][j] = '\0';
        }
    }

    void file() {
        ifstream file("users.txt");
        if (!file) {
            cout << "Error opening file,file is corrupt!" << endl;
        }
        get_education(file);
        get_institute(file);
        file.close();
    }
    void display(int user_index) {
        if (user_index < 0 || user_index >= total_users) {
            cout << " info " << endl;
            return;
        }
        if (education[user_index] != nullptr && institute[user_index] != nullptr) {
            file();
            cout << "Education: " << education[user_index] << endl;
            cout << "Institute: " << institute[user_index] << endl;
        }
        else {
            cout << "No education information found for user " << endl;
        }
    }
    ~Education() {
        for (int i = 0; i < total_users; i++) {
            delete[] education[i];
            delete[] institute[i];
        }
        delete[] education;
        delete[] institute;
        education = nullptr;
        institute = nullptr;
    }
};
class User :public Person
{
protected:
    int total_users;
    char** user_id;
    char** first_name;
    char** last_name;
    char** connections;
    char** skills;
    Education e;
    char** experience;
    const char* current_user_id;
public:
    User()
        : total_users(0), user_id(nullptr), first_name(nullptr), last_name(nullptr),
        connections(nullptr), skills(nullptr), experience(nullptr), current_user_id(nullptr)
    {}
    void file_read(ifstream& file, int total_users)
    {
        this->total_users = total_users;
        int size1 = 200, size2 = 20;
        user_id = new char* [total_users];
        first_name = new char* [total_users];
        last_name = new char* [total_users];
        connections = new char* [total_users];
        skills = new char* [total_users];
        experience = new char* [total_users];
        for (int i = 0; i < total_users; i++) {
            user_id[i] = new char[size2];
            first_name[i] = new char[size2];
            last_name[i] = new char[size2];
            connections[i] = new char[size1];
            skills[i] = new char[size1];
            experience[i] = new char[size1];
            file >> user_id[i] >> first_name[i] >> last_name[i];
            char c;
            int j = 0;
            file.get(c);
            while (file.get(c) && c != '-') {
                connections[i][j++] = c;
            }
            connections[i][j] = '\0';
            j = 0;
            while (file.get(c) && c != '-') {
                skills[i][j++] = c;
            }
            skills[i][j] = '\0';
            j = 0;
            while (file.get(c) && c != '\n') {
                experience[i][j++] = c;
            }
            experience[i][j] = '\0';
            if (user_id[i][0] != '\0' && first_name[i][0] != '\0' && last_name[i][0] != '\0' && connections[i][0] != '\0' && skills[i][0] != '\0' && experience[i][0] != '\0') {
                cout << user_id[i] << " " << first_name[i] << " " << last_name[i] << " " << connections[i] << " " << skills[i] << " " << experience[i] << endl;
            }
        }
        file.close();
    }
    void likePost(int post_id) {
        int likes;
        bool user_found = false;
        for (int i = 0; i < total_users; i++) {
            if (user_id[i] == current_user_id) {
                user_found = true;
                if (countLikes(i, post_id) >= 1) {
                    cout << "You have already liked this post." << endl;
                    return;
                }
                else {
                    likes = addLike(i, post_id);
                    break;
                }
            }
        }
        if (!user_found) {
            cout << "User not found." << endl;
            return;
        }
        else
            cout << "Post " << post_id << " now has " << likes << " likes." << endl;
    }
    int countLikes(int user_index, int post_id) {
        bool likes[10][10] = { false };
        int count = 0;
        for (int i = 0; i < 10; i++) {
            if (connections[user_index] == "connections" && likes[post_id - 1][i] == true) {
                count++;
            }
        }
        return count;
    }
    int addLike(int user_index, int post_id)
    {
        bool likes[10][10] = { false };
        int likes_count = countLikes(user_index, post_id);
        if (likes_count < 10) {
            likes[post_id - 1][likes_count] = true;
            cout << "like added" << endl;
            return likes_count + 1;
        }
        else {
            cout << "Maximum number of likes reached for this post." << endl;
            return likes_count;
        }
    }
    void SetCurrentUser() {
        current_user_id = "u";
        setid(1);

        cout << "Current user set to: " << current_user_id;
        cout << gettheid() << endl;
    }
    void educationdis()
    {
        int index = 0;
        if (index != -1)
        {
            e.display(index);
        }
    }
    virtual void ViewUsersProfile(int user_index) {
        if (user_index < 0 || user_index >= total_users) {
            cout << "Invalid user index" << endl;
            return;
        }
        educationdis();
        cout << user_id[user_index] << endl;
        cout << first_name[user_index] << endl;
        cout << last_name[user_index] << endl;
        cout << connections[user_index] << endl;
        cout << skills[user_index] << endl;
        cout << experience[user_index] << endl;
        cout << "profile displayed" << endl;
    }
    void viewconnections(int user_index)
    {
        cout << "Connections are:" << endl;
        cout << connections[user_index] << endl;
    }
    ~User() {
        for (int i = 0; i < total_users; i++) {
            delete[] user_id[i];
            delete[] first_name[i];
            delete[] last_name[i];
            delete[] connections[i];
            delete[] skills[i];
            delete[] experience[i];
        }
        delete[] user_id;
        delete[] first_name;
        delete[] last_name;
        delete[] connections;
        delete[] skills;
        delete[] experience;
        user_id = nullptr;
        first_name = nullptr;
        last_name = nullptr;
        connections = nullptr;
        skills = nullptr;
        experience = nullptr;
    }
};
class Comments {
protected:
    char** comment_id;
    char** post_id;
    char** user_no;
    char** comment_text;
    Person* person;//HAS-A relationship.
public:
    int total_comments;
    Comments() {
        total_comments = 0;
        comment_id = nullptr;
        post_id = nullptr;
        user_no = nullptr;
        comment_text = nullptr;
        person = 0;
    }
    Comments(Person* p) {
        comment_id = nullptr;
        post_id = nullptr;
        user_no = nullptr;
        comment_text = nullptr;
        person = p;
    }
    void fileread(ifstream& file, int total_comments) {
        comment_id = new char* [total_comments];
        post_id = new char* [total_comments];
        user_no = new char* [total_comments];
        comment_text = new char* [total_comments];
        int size1 = 200, size2 = 20;
        for (int i = 0; i < total_comments; i++) {
            comment_id[i] = new char[size2];
            post_id[i] = new char[size2];
            user_no[i] = new char[size2];
            comment_text[i] = new char[size1];
            int j = 0;
            char c;
            while ((c = file.get()) != '\n' && c != EOF) {
                comment_id[i][j] = c;
                j++;
            }
            comment_id[i][j] = '\0';
            j = 0;
            while ((c = file.get()) != '\n' && c != EOF) {
                post_id[i][j] = c;
                j++;
            }
            post_id[i][j] = '\0';
            j = 0;
            while ((c = file.get()) != '\n' && c != EOF) {
                user_no[i][j] = c;
                j++;
            }
            user_no[i][j] = '\0';
            j = 0;
            while ((c = file.get()) != '\n' && c != EOF) {
                comment_text[i][j] = c;
                j++;
            }
            comment_text[i][j] = '\0';
            if (comment_id[i][0] != '\0' && post_id[i][0] != '\0' && user_no[i][0] != '\0' && comment_text[i][0] != '\0') {
                cout << comment_id[i] << " " << post_id[i] << " " << user_no[i] << " " << comment_text[i] << endl;
            }
        }
        file.close();
    }
    void addComment(const char* post_id, const char* comment_text) {
        if (post_id == nullptr || comment_text == nullptr) {
            cout << "Error  invalid input." << endl;
        }
        const char* msg = "Welcome to Fast!!!";
        ofstream file("comments.txt", ios::app);
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }
        file << post_id << " : " << comment_text << endl;
        file << "User ID: " << person->gettheid() << endl;
        file << msg << endl;
        file.close();
        cout << "Comment added successfully: " << comment_text << endl;
    }
    bool Equalitycheck(const char* mys1, const char* mys2) {
        int a = 0;
        while (mys1[a] == mys2[a]) {
            if (mys1[a] == '\0') {
                return true;
            }
            a++;
        }
        return false;
    }
    void displayCommentAtIndex()
    {
        ifstream file("comments.txt");
        if (!file.is_open()) {
            cout << "Error opening file,file is corrupt!" << endl;
        }
        file >> total_comments;
        comment_id = new char* [total_comments];
        post_id = new char* [total_comments];
        user_no = new char* [total_comments];
        comment_text = new char* [total_comments];
        int s = 40, s1 = 20, s3 = 200;
        for (int i = 0; i < total_comments; i++)
        {
            comment_id[i] = new char[s];
            post_id[i] = new char[s1];
            user_no[i] = new char[s1];
            comment_text[i] = new char[s3];
            file >> comment_id[i] >> post_id[i] >> user_no[i];
            int j = 0;
            char c;
            while (file.get(c) && c != '\n' && j < s3 - 1) {
                comment_text[i][j++] = c;
            }
            comment_text[i][j] = '\0';

            if (Equalitycheck(post_id[i], "post5") && (Equalitycheck(comment_id[i], "c6") || Equalitycheck(comment_id[i], "c7") || Equalitycheck(comment_id[i], "c8"))) {
                cout << post_id[i] << " " << user_no[i] << " " << comment_text[i] << endl;
            }
        }
        file.close();
    }
    ~Comments() {
        for (int i = 0; i < total_comments; i++)
        {
            delete[] comment_id[i];
            delete[] post_id[i];
            delete[] user_no[i];
            delete[] comment_text[i];
        }
        delete[] comment_id;
        delete[] post_id;
        delete[] user_no;
        delete[] comment_text;
        comment_id = nullptr;
        post_id = nullptr;
        user_no = nullptr;
        comment_text = nullptr;
    }
};
class Company {
private:
    char** company_id;
    char** location;
    int total_companies;
public:
    void fileread(ifstream& file, int total_companies) {
        company_id = new char* [total_companies];
        location = new char* [total_companies];
        this->total_companies = total_companies;
        int size1 = 20, size2 = 200;
        for (int i = 0; i < total_companies; i++) {
            company_id[i] = new char[size1];
            location[i] = new char[size2];
            int j = 0;
            char k;
            while ((k = file.get()) != ' ') {
                company_id[i][j++] = k;
            }
            company_id[i][j] = '\0';
            while ((k = file.get()) == ' ') {}
            while (k != '\n' && k != EOF) {
                location[i][j++] = k;
                k = file.get();
            }
            location[i][j] = '\0';
            if (company_id[i][0] != '\0' && location[i][0] != '\0') {
                cout << company_id[i] << " " << location[i] << endl;
            }
        }
        file.close();
    }
    void displaycompany()
    {
        ifstream file("companies.txt");
        if (!file.is_open()) {
            cout << "Error opening file,file is corrupt!" << endl;
            return;
        }
        file >> total_companies;
        company_id = new char* [total_companies];
        location = new char* [total_companies];
        this->total_companies = total_companies;
        int size = 20, size2 = 200;
        for (int i = 0; i < total_companies; i++) {
            company_id[i] = new char[size];
            location[i] = new char[size2];
            int j = 0;
            char ch;
            while ((ch = file.get()) != ' ') {
                company_id[i][j++] = ch;
            }
            company_id[i][j] = '\0';
            while ((ch = file.get()) == ' ') {}
            while (ch != '\n' && ch != EOF) {
                location[i][j++] = ch;
                ch = file.get();
            }
            location[i][j] = '\0';
            if (company_id[i][0] != '\0' && location[i][0] != '\0') {
                cout << company_id[i] << " " << location[i] << endl;
            }
        }
        file.close();
    }

    ~Company() {
        for (int i = 0; i < total_companies; i++) {
            delete[] company_id[i];
            delete[] location[i];
        }
        delete[] company_id;
        delete[] location;
    }
};
class Post
{
protected:
    int total_post;
    char** post_id;
    char** shared_by;
    char** date;
    char** post_text;
    char** activity;
    char** liked_by;
    Comments comment;
    Company company;
    int* likes_count;
    char*** shared_with;
    int* shared_with_count;
    User a;

public:
    Post()
    {
        total_post = 0;
        post_id = nullptr;
        shared_by = nullptr;
        date = nullptr;
        post_text = nullptr;
        activity = nullptr;
        liked_by = nullptr;
        likes_count = nullptr;
        shared_with = nullptr;
        shared_with_count = nullptr;
    }
    void fileread(ifstream& file, int total_post) {
        this->total_post = total_post;
        post_id = new char* [total_post];
        shared_by = new char* [total_post];
        date = new char* [total_post];
        post_text = new char* [total_post];
        activity = new char* [total_post];
        liked_by = new char* [total_post];
        likes_count = new int[total_post];
        shared_with = new char** [total_post];
        shared_with_count = new int[total_post];
        int size1 = 20, size2 = 100;
        for (int i = 0; i < total_post; i++) {
            post_id[i] = new char[size1];
            shared_by[i] = new char[size2];
            date[i] = new char[size1];
            post_text[i] = new char[size2];
            activity[i] = new char[size2];
            liked_by[i] = new char[size2];
            shared_with[i] = nullptr;
            char ch;
            int j = 0;
            file >> post_id[i];
            file.ignore();
            file.ignore(size2, ':');
            while (j < 99 && (ch = file.get()) != '\n') {
                shared_by[i][j++] = ch;
            }
            shared_by[i][j] = '\0';
            j = 0;
            file.ignore(size2, ':');
            while (j < 19 && (ch = file.get()) != '\n') {
                date[i][j++] = ch;
            }
            date[i][j] = '\0';
            j = 0;
            file.ignore(size2, ':');
            while (j < 99 && (ch = file.get()) != '\n') {
                post_text[i][j++] = ch;
            }
            post_text[i][j] = '\0';
            j = 0;
            file.ignore(size2, ':');
            while (j < 99 && (ch = file.get()) != '\n') {
                activity[i][j++] = ch;
            }
            activity[i][j] = '\0';
            j = 0;
            file.ignore(size2, ':');
            while (j < 99 && (ch = file.get()) != '-') {
                liked_by[i][j++] = ch;
            }
            liked_by[i][j] = '\0';
            likes_count[i] = 0;
            shared_with_count[i] = 0;
            if (post_id[i][0] != '\0' && shared_by[i][0] != '\0' && date[i][0] != '\0' && post_text[i][0] != '\0' && activity[i][0] != '\0' && liked_by[i][0] != '\0') {
                cout << post_id[i] << endl;
                cout << shared_by[i] << endl;
                cout << date[i] << endl;
                cout << post_text[i] << endl;
                cout << activity[i] << endl;
                cout << liked_by[i] << endl;
            }
        }
        file.close();
    }
    void share_post(const char* user_id, int post_index)
    {
        if (post_index < 0 || post_index >= total_post)
        {
            cout << "Invalid post index." << endl;
            return;
        }
        int new_s_index = shared_with_count[post_index] + 1;
        char** new_s_with = new char* [new_s_index];
        for (int i = 0; i < new_s_index - 1; i++) {
            new_s_with[i] = shared_with[post_index][i];
        }
        new_s_with[new_s_index - 1] = new char[strlen(user_id) + 1];
        int i;
        for (i = 0; user_id[i] != '\0'; i++) {
            new_s_with[new_s_index - 1][i] = user_id[i];
        }
        new_s_with[new_s_index - 1][i] = '\0';
        delete[] shared_with[post_index];
        shared_with[post_index] = new_s_with;
        shared_with_count[post_index] = new_s_index;
        ofstream ofile("post.txt", ios::app);
        if (!ofile)
        {
            cout << "error" << endl;
        }
        ofile << "post id:" << post_id[post_index] << endl;
        ofile << "shared by" << shared_by[post_index] << endl;
        ofile << "date" << date[post_index] << endl;
        ofile << "post_text" << post_text[post_index] << endl;
        ofile << "activity" << activity[post_index] << endl;
        ofile << "liked by" << liked_by[post_index] << endl;
        ofile << endl;

        ofile.close();
        cout << "Post shared successfully." << endl;
    }
    int daysInMonth(int year, int month) {
        if (month == 2)
        {
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            {
                return 29;
            }
            else
            {
                return 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            return 30;
        }
        else
        {
            return 31;
        }
    }
    void userHome(const char post_id)
    {
        ifstream file("post.txt");
        if (!file) {
            cout << "Error opening file,file is corrupt!" << endl;
        }
        int year, month, day;
        char slash;
        file >> day >> slash >> month >> slash >> year;
        int seconds = 0;
        for (int y = 1970; y < year; y++)
        {
            if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
            {
                seconds += 366 * 24 * 60 * 60;
            }
            else
            {
                seconds += 365 * 24 * 60 * 60;
            }
        }
        for (int m = 1; m < month; m++)
        {
            seconds += daysInMonth(year, m) * 24 * 60 * 60;
        }
        seconds += (day - 1) * 24 * 60 * 60;
        time_t n = time(nullptr);
        double diff = difftime(n, seconds);
        if (diff >= 86400)
        {
            cout << "24 hours have passed since the post has been made\n";
            cout << "the connection of u1 made the following post are " << endl;
            int i = 0;
            cout << "u2 :" << "none" << endl;
            cout << shared_by[i] << post_text[i] << activity[i] << liked_by[i] << endl;
            cout << shared_by[i + 2] << post_text[i + 2] << activity[i + 2] << liked_by[i + 2] << endl;
            cout << shared_by[i + 7] << post_text[i + 7] << activity[i + 7] << liked_by[i + 7] << endl;
            cout << "the job postings according to user interest are " << endl;
            cout << shared_by[i + 1] << post_text[i + 1] << activity[i + 1] << endl;
            cout << shared_by[i + 3] << post_text[i + 3] << activity[i + 3] << endl;
            cout << shared_by[i + 7] << post_text[i + 7] << activity[i + 7] << endl;
            cout << shared_by[i + 8] << post_text[i + 8] << activity[i + 8] << endl;
            post_text = new char* [total_post];
            activity = new char* [total_post];
            liked_by = new char* [total_post];
            for (int i = 0; i < total_post; i++) {
                int size2 = 100;
                post_text[i] = new char[size2];
                activity[i] = new char[size2];
                liked_by[i] = new char[size2];
                char c = file.get();
                int j = 0;
                while (c != ':') {
                    post_text[i][j] = c;
                    c = file.get();
                    j++;
                } post_text[i][j] = '\0';
                c = file.get();
                j = 0;
                while (c != ':') {
                    activity[i][j] = c;
                    c = file.get();
                    j++;
                }activity[i][j] = '\0';
                c = file.get();
                j = 0;
                while (c != '-') {
                    liked_by[i][j] = c;
                    c = file.get();
                    j++;
                }liked_by[i][j] = '\0';
                while (c != '\n') {
                    c = file.get();
                }
            }
            delete[] post_text;
            delete[] activity;
            delete[] liked_by;
        }
        else
        {
            cout << "Less than 24 hours have passed since the post was made \n";
        }
        file.close();
    }
    void user()
    {
        a.SetCurrentUser();
    }
    void viewPost(int post_index) {
        if (post_index < 0 || post_index >= total_post) {
            cout << "Invalid post index" << endl;
            return;
        }
        cout << "Post ID: " << post_id[post_index] << endl;
        cout << "Shared by: " << shared_by[post_index] << endl;
        cout << "Date: " << date[post_index] << endl;
        cout << "Post Text: " << post_text[post_index] << endl;
        cout << "Activity: " << activity[post_index] << endl;
        cout << "Liked by: " << liked_by[post_index] << endl;
        cout << "Comments:";
        comment.displayCommentAtIndex();
    }
    void displaylikedbylist(int post_index)
    {
        if (post_index < 0 || post_index >= total_post) {
            cout << "Invalid post index" << endl;
        }
        cout << "list of people who have liked =" << liked_by[post_index] << " shared by  " << shared_by[post_index] << endl;
    }
    void showjobposting(int post_index1, int post_index2, int post_index3, int post_index4)
    {
        if (post_index1 < 0 || post_index1 >= total_post || post_index2 < 0 || post_index2 >= total_post || post_index3 < 0 || post_index3 >= total_post || post_index4 < 0 || post_index4 >= total_post) {
            cout << "Invalid post index" << endl;
        }
        company.displaycompany();
        cout << "Qualification c3" << post_text[post_index1] << endl;
        cout << "Qualification c5" << post_text[post_index2] << endl;
        cout << "Qualification c2" << post_text[post_index3] << endl;
        cout << "Qualification c3" << post_text[post_index4] << endl;
    }
    void Search(const char* key) {
        bool search = false;
        for (int i = 0; i < total_post; i++) {
            bool mat = false;
            int j = 0;
            while (post_text[i][j] != '\0') {
                if (post_text[i][j] == key[0]) {
                    int k = j + 1;
                    int l = 1;
                    while (key[l] != '\0' && post_text[i][k] == key[l]) {
                        k++;
                        l++;
                    }
                    if (key[l] == '\0') {
                        mat = true;
                        break;
                    }
                }
                j++;
            }
            if (mat) {
                search = true;
                cout << "Post " << post_id[i] << ": " << post_text[i] << endl;
            }
            else {
                j = 0;
                while (activity[i][j] != '\0') {
                    if (activity[i][j] == key[0]) {
                        int k = j + 1;
                        int l = 1;
                        while (key[l] != '\0' && activity[i][k] == key[l]) {
                            k++;
                            l++;
                        }
                        if (key[l] == '\0') {
                            mat = true;
                            break;
                        }
                    }
                    j++;
                }
                if (mat) {
                    search = true;
                    cout << "Activity in Post " << post_id[i] << ": " << activity[i] << endl;
                }
                else {
                    j = 0;
                    while (liked_by[i][j] != '\0') {
                        if (liked_by[i][j] == key[0]) {
                            int k = j + 1;
                            int l = 1;
                            while (key[l] != '\0' && liked_by[i][k] == key[l]) {
                                k++;
                                l++;
                            }
                            if (key[l] == '\0') {
                                mat = true;
                                break;
                            }
                        }
                        j++;
                    }
                    if (mat) {
                        search = true;
                        cout << "Liked by User " << liked_by[i] << " in " << post_id[i] << endl;
                    }
                }
            }
        }
        if (!search) {
            cout << "No match exists" << endl;
        }
    }
    ~Post()
    {
        for (int i = 0; i < total_post; i++)
        {
            delete[] post_id[i];
            delete[] shared_by[i];
            delete[] date[i];
            delete[] post_text[i];
            delete[] activity[i];
            delete[]likes_count;
            delete[] liked_by[i];
        }
        delete[] post_id;
        delete[] shared_by;
        delete[] date;
        delete[] post_text;
        delete[] activity;
        delete[] liked_by;
        delete[] likes_count;
        post_id = nullptr;
        shared_by = nullptr;
        date = nullptr;
        post_text = nullptr;
        activity = nullptr;
        liked_by = nullptr;
        likes_count = nullptr;
    }
};
class Page {
protected:
    int total_pages;
    char** page_id;
    char** title_page;
public:
    Page() {
        total_pages = 0;
        page_id = nullptr;
        title_page = nullptr;
    }
    void fileread(ifstream& file, int total_pages) {
        char** page_id = new char* [total_pages];
        char** title_page = new char* [total_pages];
        int size1 = 20;
        int size2 = 100;
        char ch;
        for (int i = 0; i < total_pages; i++) {
            page_id[i] = new char[size1];
            title_page[i] = new char[size2];
            int j = 0;
            while ((ch = file.get()) != ' ') {
                page_id[i][j++] = ch;
            }
            page_id[i][j] = '\0';
            j = 0;
            while ((ch = file.get()) != '-') {
                title_page[i][j++] = ch;
            }
            title_page[i][j] = '\0';
            file.get();
            file.get();
            cout << page_id[i] << " " << title_page[i] << endl;
        }
        file.close();
    }
    ~Page() {
        for (int i = 0; i < total_pages; i++) {
            delete[] page_id[i];
            delete[] title_page[i];
        }
        delete[] page_id;
        delete[] title_page;
        page_id = nullptr;
        title_page = nullptr;
    }
};
class Date
{
    char** date;
    int total_post;
    Post* t;
public:
    Date()
    {
        total_post = 0;
        date = nullptr;
    }
    Date(Post* a)
    {
        total_post = 0;
        date = nullptr;
        t = a;
    }
    void postread()
    {
        ifstream file("post.txt");
        if (!file.is_open()) {
            cout << "Error opening file,file is corrupt!" << endl;
        }
        file >> total_post;
        date = new char* [total_post];
        for (int i = 0; i < total_post; i++) {
            int size = 20;
            date[i] = new char[size];
            int j = 0;
            char c;
            while ((c = file.get()) != ':') {
                date[i][j++] = c;
            }
            date[i][j] = '\0';
            cout << date[i] << endl;
            while ((c = file.get()) != '\n')
            {
                continue;
            }
        }
        file.close();
    }
    void get_date()
    {
        t->daysInMonth(2017, 11);
        t->userHome(0);
    }
    ~Date()
    {
        delete[]date;
    }
};
class Activity : public Post
{
private:
    int type;
    char* value;
    char** activity_type;
public:
    Activity()
    {
        type = 0;
        value = NULL;
        activity_type = nullptr;
    }
    void setActivity()
    {
        ifstream file("post.txt");
        if (!file.is_open()) {
            cout << "Error opening file,file is corrupt!" << endl;
        }
        int total_post;
        file >> total_post;
        fileread(file, total_post);
    }
    char* getActivity()
    {
        ifstream file("post.txt");
        if (!file.is_open()) {
            cout << "Error opening file,file is corrupt!" << endl;

        }
        file >> total_post;
        cout << "Total posts: " << total_post << endl;
        for (int i = 0; i < total_post; i++) {
            activity_type[i] = activity[i];
            if (i == 0)
                cout << value[i] << " :Type1" << endl;
            else if (i == 1)
                cout << value[i] << " :Type2" << endl;
            else if (i == 2)
                cout << value[i] << " :Type3" << endl;
            else if (i == 3)
                cout << value[i] << " :Type2" << endl;
            else if (i == 4)
                cout << value[i] << " :Type4" << endl;
            else if (i == 5)
                cout << value[i] << " :Type1" << endl;
            else if (i == 6)
                cout << value[i] << " :Type4" << endl;
            else if (i == 7)
                cout << value[i] << " :Type2" << endl;
            else if (i == 8)
                cout << value[i] << " :Type3" << endl;
            else if (i == 9)
                cout << value[i] << " :Type3" << endl;
            else
                cout << "Our application doesn't support types Eating, Travelling, Drinking, Watching, etc. at the moment." << endl;
        }
    }
    ~Activity()
    {
        delete[]value;
        for (int i = 0; i < total_post; i++) {
            delete[]activity_type;
        }
        value = nullptr;
        delete[] activity_type;
        activity_type = nullptr;
    }
};
int main()
{
    ifstream file_user("user.txt");
    if (!file_user.is_open()) {
        cout << "Error opening file,file is corrupt!" << endl;
    }
    int total_users;
    file_user >> total_users;
    const int u = total_users;
    cout << "Total users: " << total_users << endl;
    User* users = new User[u];
    for (int i = 0; i < total_users; i++) {
        users[i].file_read(file_user, total_users);
    }
    cout << "-------------------------------------------------------------------------" << endl;
    users->SetCurrentUser();
    users->ViewUsersProfile(0);
    users->addLike(0, 2);
    users->viewconnections(0);
    delete[] users;
    Person person;
    person.setid(1);
    Comments comm(&person);
    comm.addComment("post1", "Welcome to Fast!!");
    ifstream file_post("post.txt");
    if (!file_post.is_open()) {
        cout << "Error opening file,file is corrupt!" << endl;
    }
    int total_post;
    file_post >> total_post;
    const int p = total_post;
    cout << "Total posts: " << total_post << endl;
    Post* post = new Post[p];
    for (int i = 0; i < total_post; i++) {
        post[i].fileread(file_post, total_post);
    }
    post->share_post("u1", 1);
    cout << "search" << endl;
    post->Search("u1");
    post->viewPost(4);
    post->displaylikedbylist(4);
    post->showjobposting(1, 3, 7, 8);
    post->userHome(1);
    delete[] post;
    return 0;
}