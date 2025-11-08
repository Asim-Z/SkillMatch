# Skill Matcher

A platform that connects people based on skills they have or need. Users can post skills, search for others, and rate each other based on trust.

## Features

- User accounts with login
- Post skills you have or request skills you need
- Search for users by skill with trust score filtering
- Rate other users to build trust scores
- Messaging between users
- Data saved to files

## Implementation

Key functions:
- **skillSearch()** - search users by skill and filter by trust level
- **requestView()** - browse requests with trust filtering
- **mainPage()** - main menu navigation
- **rateUser()** - rating system for trust scores
- File loading/saving for persistent data

## Running the Program
```bash
gcc *.c -o skill_matcher
./skill_matcher
```

## Usage

1. Register or login
2. Post your skills or create requests
3. Search for people with skills you need
4. Rate users after working with them
5. Use trust scores to find reliable people

## Technologies

C, file I/O, custom data structures, sorting algorithms
