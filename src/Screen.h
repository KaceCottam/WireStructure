#ifndef SCREEN_H
#define SCREEN_H
class Screen {
  public:
    virtual void loadResources() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void unloadResources() = 0;
    virtual ~Screen();
};
#endif // ! SCREEN_H

