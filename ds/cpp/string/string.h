#ifndef STRGIN_H
#define STRING_H

class String {
private:
    char *str_;
    int len_;

public:
    String();
    String(const char *s);
    String(const String& rhs);
    ~String();
    
    // String* operator&() { return this; }
    // const String* opeartor&() { return this; }
    
    // String& operator= (const String& rhs) { /* memberwise copy */ }

};

#endif