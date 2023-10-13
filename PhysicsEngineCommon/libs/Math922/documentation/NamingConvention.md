[Return](../README.md)

# Naming convention

## General

- Use **PascalCase** for: 
  - class names
  - public methods
  - public variables
  - public constants
  - public enums
  - namespace
- Use **camelCase** for private methods
- Use **_camelCase** for private variables
  
### Use of struct

- Use `struct` for list of attributes, can contain operators but no methods

Ex:
```c++
struct Position 
{
    float X;
    float Y;
};
```

### Use of static

- Use `static` in classes if the function use 2+ instance of the class inside

Ex:
```c++
static float Distance(Vec2 from, vec2 to); // Get the distance between 2 vec2
float Length(); // Get the length of the vec
```