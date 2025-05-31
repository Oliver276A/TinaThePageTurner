# Automatic Page Turner - Final Report

Dawson College - MakerSPACE  
Student Name: Oliver Mui  
Submitted to: Professor Joel Trudeau  
Date submitted: 2025-06-01    

## Introduction

One of the issues that bother many musicians is that of turning pages, which greatly inhibits their performance (to the point where in some concerts there is a dedicated person to turn the pages for the musician). Some use electronic tablets as a substitute but it is expensive and inconvenient for quick annotation. I believe that many musicians would like to be able to enjoy the convenience of having the pages turned for them while using their physical book or sheet music, and this inspired me to create this project, that is to create a prototype of an automatic page turner dedicated for musicians.   

This report will cover the planning, implementation and the results of this project, in an attempt to provide some insights on the development of such device.    

## Project Description

### Inspiration

The inspiration comes from my personal frustration over turning pages while trying to play a difficult piece. I do not own an electronic tablet, meaning my only options are to flip the pages myself or simply memorise the music.     

### Objectives

Several similar projects exist but they present a few problems: Firstly, most of such projects are optimized for book reading and not for musicians, so they either lay completely flat, or they require an extensive setup. The one project that is made for the piano requires the pianist to attach special magnets. To me, all these reduce the attractiveness of page flipping machines to musicians.   

Thus, the goal of this project is to create a prototype of an **autonomatic** machine that is capable of turning pages while being **adapted to the needs of musicians**, that is:
- Lightweight and flexible for different needs
- Requires *minimal* setup and easy to use
- Simple, cheap and reliable
- Provides consistent result    

With limited resources, time and skills, I do not expect to create a perfectly functional machine. However, through the creation of a **basic prototype**, I hope to demonstrate that such device is feasible and can be perfected and developped into an real product, while sharing my experience which I hope would be of value to someone who wants to develop something similar.     

### Design and Planning

The first question to answer, and this will prove to be the most important question, is how the pages should be picked up. Static electricity and magnets do not seem practical, so I decided to rely on the traditional mechanical method, which exist on many existing models - using a wheel to lift the pages.    

Then, when the pages are lifted, how should they be flipped to the left? My initial idea was to use a sliding bar. However, this will require gears and rails for the bar to slide upon, which are not only complicated, but can also end up being heavy. I opted for a stick attached to a servo in the end, which is simpler and more readily available.    

Some kind of user interaction is needed to trigger the page turn. I did not think about this in much detail as this can be any form of button or sensor depending on the need.    

Lastly, one single structure is needed to connect all these components. At first, inspired from book clips, I wanted to use those clips as the platform of my device, which allows for easy clipping to any books. However, upon further consideration, I discovered two problems: First, it would not work for books that lacks a hard cover which cannot support the weight of the device; Second, the device moves in such a big distance that a simple clip would not be enough.    

Thus, afterwards, I adopted the idea of a light platform to which books are clipped by a wheel and a stick which turn the pages. Tina "the Page" Turner was born.   

[Brainstorming doodle](/images/doodle1.png) [Brainstorming doodle](/images/doodle2.png)

## Implementation

### Hardware

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

The wiring is shown in the following schematic:

