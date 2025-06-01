# Automatic Page Turner - Final Report

Dawson College - MakerSPACE  
Student Name: Oliver Mui  
Submitted to: Professor Joel Trudeau  
Date submitted: 2025-06-01    

## 1. Introduction

One of the issues that bother many musicians is that of turning pages, which greatly inhibits their performance (to the point where in some concerts there is a dedicated person to turn the pages for the musician). Some use electronic tablets as a substitute but it is expensive and inconvenient for quick annotation. I believe that many musicians would like to be able to enjoy the convenience of having the pages turned for them while using their physical book or sheet music, and this inspired me to create this project, that is to create a prototype of an automatic page turner dedicated for musicians.   

This report will cover the planning, implementation and the results of this project, in an attempt to provide some insights on the development of such device.    

## 2. Project Description

### 2.1. Inspiration

The inspiration comes from my personal frustration over turning pages while trying to play a difficult piece. I do not own an electronic tablet, meaning my only options are to flip the pages myself or simply memorise the music.     

### 2.2. Objectives

Several similar projects exist but they present a few problems: Firstly, most of such projects are optimized for book reading and not for musicians, so they either lay completely flat, or they require an extensive setup. The one project that is made for the piano requires the pianist to attach special magnets. To me, all these reduce the attractiveness of page flipping machines to musicians.   

Thus, the goal of this project is to create a prototype of an **autonomatic** machine that is capable of turning pages while being **adapted to the needs of musicians**, that is:
- Lightweight and flexible for different needs
- Requires *minimal* setup and easy to use
- Simple, cheap and reliable
- Provides consistent result    

With limited resources, time and skills, I do not expect to create a perfectly functional machine. However, through the creation of a **basic prototype**, I hope to demonstrate that such device is feasible and can be perfected and developped into an real product, while sharing my experience which I hope would be of value to someone who wants to develop something similar.     

### 2.3. Design and Planning

The first question to answer, and this will prove to be the most important question, is how the pages should be picked up. Static electricity and magnets do not seem practical, so I decided to rely on the traditional mechanical method, which exist on many existing models - using a wheel to lift the pages.    

Then, when the pages are lifted, how should they be flipped to the left? My initial idea was to use a sliding bar. However, this will require gears and rails for the bar to slide upon, which are not only complicated, but can also end up being heavy. I opted for a stick attached to a servo in the end, which is simpler and more readily available.    

Some kind of user interaction is needed to trigger the page turn. I did not think about this in much detail as this can be any form of button or sensor depending on the need.    

Lastly, one single structure is needed to connect all these components. At first, inspired from book clips, I wanted to use those clips as the platform of my device, which allows for easy clipping to any books. However, upon further consideration, I discovered two problems: First, it would not work for books that lacks a hard cover which cannot support the weight of the device; Second, the device moves in such a big distance that a simple clip would not be enough.    

Thus, afterwards, I adopted the idea of a light platform to which books are clipped by a wheel and a stick which turn the pages. Tina "the Page" Turner was born.   

![Brainstorming doodle](/images/doodle.png)

## 3. Implementation

### 3.1. Hardware

- **Electronic Components**
    1. 180 degrees servo (Feetech FS90) - For the turning stick
    2. Continuous servo (Feetech FS90R) - For the wheel
    3. Ultrasonic sensor (HC-SR04) - Need I say more?   
- **Structural**
    1. Structural material of choice - I used some hard cardboard which is readily available but wood or metal will also work
    2. Adhesives - Some tape and some hot glue
    3. Torsion springs - This is to put pressure between the page and the wheel while allowing books to be placed on the platform; I realized it is very difficult to install torsion spring, so I came up with using a clothespeg which is readily available! (Note that the angle cannot be too small - More on this later.)
- **Tools**
    1. Scissors and cutters
    2. Hot glue gun

**Creating the Frame of the Machine**    
![Diagram of the frame](/images/frame.png)

**Installation of Electronic Components**     
*Overview*   
![Photo of Tina](/images/overview.jpg)
*Ultrasonic sensor*    
![Photo of ultrasonic sensor installed](/images/us-sensor.jpg)
- The ultrasonic sensor can be installed any way that is convenient
- I chose to tape the connectors on the top right of the frame simply because it is the easiest to install; It is also easy for a pianist to tilt their head to trigger the page turner
*Stick*
![Photo of servo and stick](/images/stick.jpg)
- The stick is secured onto the 180 degree servo using a screw
- Note that the stick is wrapped with clear tape in order to make it smoother and prevent damaging the pages
- The ensemble is attached to the middle of the frame by hot glue
*Wheel*
![Photo of wheel attached to clothespeg](/images/wheel-and-clothespeg.jpg)
- The wheel must be secured onto the continuous servo using a screw, otherwise it could fall off
- The servo is attached to a stick, which itself is attached to the clothespeg using hot glue
- The clothespeg is attached to the horizontal platform such that the wheel touches the back platform
- A small triangular piece of cardboard was added to strengthen the connection     
*Arduino Uno and Breadboard*
![Wiring photo](/images/wiring-photo.jpg)
- The Uno is secured by screws and the breadboard by adhesives
- The wires are hidden from view by placing the Uno and the breadboard in the back of the platform    

The wiring is shown in the following schematic:     
![Schematic diagram](/images/schematic.png)  

Note that it is common practice to power servos with an external power supply, as the Arduino Uno does not provide sufficient current for the servos. However, during the course of this project, I did not notice significant power issues apart from the following: 1) The stick servo sometimes have trouble pushing the pages, especially when the page turner turns more than one pages by accident, and 2) A slight buzzing of the servos, which upon research seems to be linked to power issues. At any rate, the stick is not supposed to push more than one page, and the slight buzzing gets covered by the sound of the piano, and thus I did not connect an external power supply.    

### 3.2. Code

With the hardware installed, it was time to hop onto my laptop and start coding.

I first wrote a basic program with the wheel simply turning at a certain speed and the stick pushing the pages. To my surprise it already worked but three issues arose:    

1. Machine starts right away, making it difficult to put books on the platform without accidentally triggering the page turning mechanism
    - **Solution**: This is fixed by adding an initialization mechanism. The following code allows for activating the machine by placing one's hand 5cm (not likely to be triggered by accident) within the ultrasonic sensor for 6 cumulative ticks (0.5 second each):     
    ```C++
    int i = 0;
    while(i < 6) {
        getDistance();
        if (distance < 5) {
            i ++;
            delay(500);
        }
    }
    ```
    - I did not make i go back to zero in case the sensor glitches and detects an unreasonably big distance and reset the counter again.
    - Similarly, a turning off mechanism is added but this time, the counter will reset if the sensor senses a big distance again
    ```C++
    // Turning off mechanism
    if ((distance <= 5) and (robotOn = true)) { // If very close, trigger the mechanism

        int j = 0; // Make an integer

        while(j < 6) {
            getDistance(); // Get new distance
            Serial.println(distance);
            if (distance <= 5) { // Very close
                j ++; // Count six consequetive times (3 seconds)
                delay(500);
            }
            else {break;} // If far again, proceed
        }

        if (j >= 6) {
            stick.write(0); // Stick returns to neutral position
            Serial.println("Turning off!");
            while(true) {} // If more than 3 seconds, shut down
        }
    }
    ```

2. Glitchy ultrasonic sensor readings, triggering the turning mechanism when not needed
    - **Solution**: When the ultrasonic sensor senses a distance less than 30cm, it checks shortly afterwards again. If the distance is still less than 30cm, the turning mechanism is triggered.
    ```C++
    if ((distance > 5) and (distance < 30)) { // 30 seems to be a reasonable distance to trigger the robot. Also, less than 5cm is excluded because of the turning off mechanism
    
        delay(100); // Wait for one more tick to check if glitching
        getDistance();
        Serial.println(distance);
        if ((distance > 5) and (distance < 30)) { // Not glitching, proceed
        // The page turning mechanism follows...
    ```

3. The rubber wheel fails to pick up any pages some times, and pick up more than one pages the other times
    - This issue proves to be the central challenge of the project. As it concerns both software and hardware, I will talk about this in the next section.    

### 3.3. The Wheel Dilemma

### 3.4. Sensor Documentation