# Instructions

Update this document where indicated [look for the brackets!]. Replace text inside the brackets with your own information. For example: Course Name should be the name of this course, and not the generic words "Course Name".

<br>

## [ Project and Portfolio I: Computer Science ]

- **[ Richard Luna ]**
- **[ 11/20/26 ]**

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.

Update the information below to demonstrate your knowledge on this topic.

**1. Using Terminal, there are essential commands to know.**

List the correct Terminal commands to do the actions listed below. Replace **CMD** with the correct command sequence. You can keep or enhance the brief description.

**The last bullet provides an example**.

- [ `clear` ]: Clear the Screen
- [ `pwd` ]: Print the "Working Directory"
- [ `ls` ]: List files and folders
- [ `ls -a` ]: List files and folders, including invisible files
- [ `ls -lah` ]: List all files and folders, in human readable form
- [ `cd "folder/path` ]: Change directory
- [ `cd /` ]: Change directory, go to root directory
- [ `cd ~` ]: Change directory and go to user home directory
- [ `cd ..` ]: Change directory, go up one folder level
- [ `cd ../..` ]: Change directory, go up two folder levels
- [ `cd ~/Desktop` ]: Change directory to my desktop!

**2. Using Terminal...**

**Folder Drop:** Try typing "cd" followed by a space, and then drag a folder into terminal and press return. Test this out and describe your results below.

[ /c/Users/xsava This is what I got which was the file parent. ]

## Topic: Version Control & Git

Version control, also known as revision control, records changes to a file or set of files over time so that you can recall specific versions later. In this class, we are learning Git. Update the information below where indicated.

**1. There are three types of version control.**

[ Local version control: Stores files history on one computer. It lets you  recover earlier versions, but losing that computer's history can mean losing those versions.
  Centrialized version control: Use one central server to store the shared history. Developers connect to that server to get updates and submit changes
  Distrubuted version control: Give developers local copies of the repository and its history. They can commit locally and share changes with a remote repository. Git uses this approach.]

**2. Using Terminal, there are also essential Git commands to know.**

List the correct Git commands to do the actions listed below in Terminal. Replace CMD with the correct command and keep or enhance the brief description.

- [ `git clone https://github.com/DarkEyeRichi/LUNA_RICHARD_CSREPO.git` ]: Clone a repository
- [ `git config --global user.name "Richard Luna"` ]: Set-up a global user name
- [ `git config --global user.email` ]: Set-up a global email address (to match my GitHub account email)
- [ `git status` ]: Shows the current state of your directory and staging area
- [ `git add -- docs/RLuna-VersionControl.md` ]: Add modified files to the next commit
- [ `git commit -m "Describe the completed change"` ]: Make a commit with a new message
- [ `git log` ]: Show my commit history
- [ `git --help` ]: Show Git's help screen

**3. Connecting to GitHub using Terminal.**
HTTPS is the the correct way to connect to GitHub in this course. Describe how you connect to GitHub from Terminal using this protocol. What steps do you take?

[ open the rep in github and open the terminal and run git clone with the copied repo url. Enter the cloned folder with cd. use gitpull and gitpush. ]

**4. Using .gitignore and Why it's Important**  
Most repositories contain a .gitignore file.

- What is the purpose of this file?
  <br>
  [A gitignore file specifies untracked files and folders Git should normally ignore. It keeps generated files and local settings out of commits. Adding a rule does not automatically stop tracking the files.]

- What is the "**.DS_Store**" file and why would you want to ignore it?
  <br>
  [This is a MacOS finder metadata file used for folder-display information. It is normally ignored because those local display settings are not part of the project settings source code]

- What other file or folder would you want to add to a .gitignore file and why?
  <br>
  [Your project provides a concerte example .vs/ contains VS local settings and caches. Ignoring it keeps those generated files out of your repository and avoids trying to stage locked cache files.]

<br>

# Reference Links

Replace the example references below with your own links and recommended resources. It is acceptable to provide multiple links for a single topic and to use material provided to you in this class. You are encouraged to link to your own independent research as well.

[ Research Summary: What resource(s) did you find most helpful this past week and why? ]

**Terminal Commands**  
[Site Address](https://www.gnu.org/software/bash/manual/html_node/Bourne-Shell-Builtins.html)

**Three Types of Version Control**  
[Site Address](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)

**Git Commands**  
[Site Address](https://git-scm.com/docs/git)

**Connecting to GitHub using Terminal**  
[Site Address](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

**Using .gitignore and Why it's Important**  
[Site Address](https://git-scm.com/docs/gitignore)
