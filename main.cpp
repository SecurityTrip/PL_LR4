#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>


class Time{
private:
    unsigned short int hour, minute, second;
    int seconds;
    std::string timer;
public:
    Time(){
        hour=0;
        minute=0;
        second=0;
        seconds = 0;
    }

    Time(int &h){
        if(h >= 0 && h <= 24) {
            hour = h;
            minute = 0;
            second = 0;
        }
        seconds = second + minute*60 + hour*60*60;
    }

    Time(int &h, int &m){
        if((h >= 0 && h <= 24) && (m>=0 && m <= 60)) {
            hour = h;
            minute = m;
            second = 0;
        }
        seconds = second + minute*60 + hour*60*60;
    }

    Time(int &h, int &m, int &s){
        if((h >= 0 && h <= 24) && (m>=0 && m <= 60) && (s>=0 && s <= 60)) {
            hour = h;
            minute = m;
            second = s;
        }
        seconds = second + minute*60 + hour*60*60;
    }

    Time(const Time &T){
        this->second = T.second;
        this->hour = T.hour;
        this->minute = T.minute;
        this->seconds = T.seconds;
    }

    ~Time() = default;

    int time_to_seconds(){
        return seconds;
    }

    int inInt() const {
        return seconds;
    }

    Time normalize(int& t){
        int h,m,s;
        h=t/60/60;
        t=t-h*60*60;
        m=t/60;
        t=t-m*60;
        s=t;
        return Time(h,m,s);
    }

    void rebuild_time(){
        if(hour >= 12){
            hour = hour - 12;
            timer = "PM";
        } else{
            timer = "AM";
        }

    }


    friend std::ostream& operator<< (std::ostream&, const Time&);
    friend std::istream& operator>> (std::istream&, Time&);

    Time operator = (std::string& t);

};

std::vector<int> split (const std::string& s, const std::string& delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));
        std::vector<int> tmp;
        for(auto & re : res){
            tmp.push_back(stoi(re));
        }
        return tmp;
    }

int compare(const Time &a, const Time &b, const double epsilon = 0.00001) {
    return ((std::fabs(a.inInt() - b.inInt()) < epsilon) ? 0 :
            (a.inInt() < b.inInt()) ? -1 : 1);
}

bool operator==(const Time &a, const Time &b) {
    return compare(a, b) == 0;
}

bool operator!=(const Time &a, const Time &b) {
    return compare(a, b) != 0;
}

bool operator<(const Time &a, const Time &b) {
    return compare(a, b) < 0;
}

bool operator>(const Time &a, const Time &b) {
    return compare(a, b) > 0;
}

bool operator<=(const Time &a, const Time &b) {
    return compare(a, b) <= 0;
}

bool operator>=(const Time &a, const Time &b) {
    return compare(a, b) >= 0;
}

std::ostream& operator<< (std::ostream& out, const Time &T) {
    if(T.timer.size() == 0 ) {
        if (T.hour < 10) out << "0" << T.hour << ":";
        else out << T.hour << ":";

        if (T.minute < 10) out << "0" << T.minute << ":";
        else out << T.minute << ":";

        if (T.second < 10) out << "0" << T.second;
        else out << T.second;

        return out;
    } else{
        if (T.hour < 10) out << "0" << T.hour << ":";
        else out << T.hour << ":";

        if (T.minute < 10) out << "0" << T.minute << ":";
        else out << T.minute << ":";

        if (T.second < 10) out << "0" << T.second;
        else out << T.second << T.timer;

        return out;
    }
}

std::istream& operator>>(std::istream & in, Time & T) {
    std::string in_str;
    in >> in_str;

    std::string delimiter = ":";
    std::vector<int> tmp = split(in_str,delimiter);

    T = Time(tmp[0],tmp[1],tmp[2]);

}

Time Time::operator=(std::string& t) {
    std::string delimiter = ":";
    std::vector<int> tmp = split(t,delimiter);

    Time T = Time(tmp[0],tmp[1],tmp[2]);

    return T;
}

Time operator + (Time& T1, Time& T2){

    Time tmp;
    int tmp_sec = T1.time_to_seconds() + T2.time_to_seconds();
    if (tmp_sec <= 24*60*60 + 59*60 + 59) return tmp.normalize(tmp_sec);
    else return tmp;

}

Time operator - (Time& T1, Time& T2){
    Time tmp;
    int tmp_sec = T1.time_to_seconds() - T2.time_to_seconds();
    if (tmp_sec > 0) return tmp.normalize(tmp_sec);
    if (tmp_sec == 0) return tmp;
    if (tmp_sec < 0) return tmp;

}



int main() {
    std::ifstream in_file;
    in_file.open("input.txt");
    Time T1,T2;
    unsigned short int flag;
    in_file >> flag;
    in_file >> T1;
    in_file >> T2;
    in_file.close();

    std::ofstream out_file;
    out_file.open("output.txt");
    switch(flag) {
        case 1: {
            Time tmp;
            tmp = T1 + T2;
            out_file << tmp;
            break;
        }
        case 2: {
            out_file << T1 - T2;
            break;
        }
        case 3: {
            out_file << T1 << " ";
            T1.rebuild_time();
            out_file << T1 << std::endl;

            out_file << T2 << " ";
            T2.rebuild_time();
            out_file << T2 << std::endl;
            break;
        }
        case 4: {
            out_file << T1.time_to_seconds() << std::endl;
            out_file << T2.time_to_seconds() << std::endl;
            break;
        }
        case 5:{
            if(T1>T2) {out_file << T1 << " > " << T2 << std::endl; break;}
            if(T1<T2) {out_file << T1 << " < " << T2 << std::endl; break;}
            if(T1>=T2) {out_file << T1 << " >= " << T2 << std::endl; break;}
            if(T1<=T2) {out_file << T1 << " <= " << T2 << std::endl; break;}
            if(T1==T2) {out_file << T1 << " = " << T2 << std::endl; break;}
            break;
        }
    }
    out_file.close();

    return 0;
}