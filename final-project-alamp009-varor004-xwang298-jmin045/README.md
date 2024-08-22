
# Digital Task Planner

 > Authors: \<[Adelyn Lampley](https://github.com/addyhana)\>,\<[Jiajie Min](https://github.com/jiajiemin)\>,\<[Vrisha Arora](https://github.com/vrishaarora)\>,\<[Xuanyuan Wang](https://github.com/sxw82475)\>.
 
> We are going to design a digital task planner that can allow users to manage their daily tasks, and view an optimized schedule for completing them. 

>The reason we are interested in implementing this idea is that, as students, we have a lot of tasks to manage during our day-to-day lives. A functional planner can help us manage and view our tasks in an organized fashion, reducing the stress of remembering everything at once.

>The digital planner is going to be implemented in C++, using cmake and Valgrind to assist with development.

>The program will prompt the user if they would like to restore a save file (in the form of a .txt file), they will also have the ability to add tasks, edit tasks, view tasks (sorted by date, category, or priority), delete tasks, mark tasks as complete, and request an optimized schedule of tasks. Each task has a title, category, description, priority, and due date associated with them that will be prompted to the user. 

>The features of our project:
 >1. The user can choose the way to organize their task either by deadlines, priority, or category.
 >2. The user can edit tasks directly if they need to update the information.
 >3. When the user finished a task, they are able to mark it as complete and it will be hidden from scheduling and editing options (but may still be deleted).
> 4. The user will be able to save any changes they've made during the program's runtime to their machine. 



>## User Interface Specification
> **Functional Requirements:**
   * Task Management: Listing tasks, creating new tasks, editing tasks, deleting tasks, etc.
   * Time Management: Setting task deadlines, sorting tasks by date, creating optimized schedule based on date+priority, etc. 
> **Interface Design:**
   * Main Page Layout: Task list, calendar view, etc. <br />
> **User Interaction:** 
   * Interface Navigation: Design easy-to-navigate menu structure and page transitions.
   * Task Operations: Support quick task editing, task deleting and other convenient operations. <br />
 > **Input/Output:**
   * Input Formats: Define formats for user input of task information, such as task title, description, deadline, etc.
   * Output Formats: Determine display formats for task lists and scheduled list.

### Navigation Diagram
> The image below is the User Naviation Diagram,
> ![UND](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/User%20Navg%20Diagram.jpg?raw=true)

> At the beginning of the program, the user will be prompted with the main menu, presenting a list of options for the user. On the first run, it will also prompt if information should be pulled from a file saved to the user's machine. Otherwise, five options will be presented. If the user chooses to add a task, they will be prompted to fill in the appropriate information of each task (Title, Date, Description, Category), and then it will be added to their current list. Additionally, the user may choose to edit a task, which they will be similarly prompted to identify which task to edit, and what aspect of the task they would like to edit. If a user decided to delete a task, they will also be prompted to identify the correct task to delete and accept an additional confirmation message to ensure they do not make a mistake. If choosing to complete a task, a similar identification process will be prompted and confirmation message presented. Lastly, the user will receive the option to view their tasks, and choose the way in which they want to view them- whether sorted by upcoming date, the category they're in, or viewing past (completed) tasks. After they are done, the program will terminate after any changed information will be saved to the file if they had provided a file previously. 

### Screen Layouts
> When user open this project the first page would be the Menu page, with different options(picture below is the main menu):
> ![SL](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-Menu.jpg?raw=true)
>
> 
>
> When user choose 1,which is ADD TASK, the screen would be below:
> ![SL-ADD](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-Add%20Task.jpg?raw=true)
>
> 
>
> When user choose 2,which is VIEW TASK, the screen would be below:
> ![SL-VIEW](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-View.jpg?raw=true)
>
> 
>
> When user choose 3,which is EDIT TASK, the screen would be below:
> ![SL-EDIT](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-Edit.jpg?raw=true)
>
> 
>
> When user choose 4,which is DELETE TASK, the screen would be below:
> ![SL-DELETE](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-Delete.jpg?raw=true)
>
> 
>
> When user choose 5,which is COMPLETE TASK, the screen would be below:
> ![SL-COMPLETE](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/blob/master/IMG/SL-Complete.jpg?raw=true)
>
> 
>
> When user choose 6,which is QUIT, the program end, nothing show on the screen.

## Class Diagram
> By utilizing the base epics and user stories our team had decided on for the core features of our program, we have created the following UML Diagram to serve as a basis for implementation. As more user stories arise, and implementation begins, the UML Diagram is subject to change. 
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/fc64bb6a-8dc5-48a8-8704-150dc8a68085)
> The Task object will be the class that stores all the information of individual tasks, filled only with getter and setter functions to be able to edit the information in a previously initialized task. This class utilizes the Date class as a helper class, to separately store Date information, and produce cleaner code when comparing multiple dates together. This Date class also features a string return function, so it holds the capability to output the Date as both numerical (i.e. 01/01/2024), and alphabetical (i.e. January 1st, 2024). To control the collection of tasks the user wants to manipulate in the program, we will create the TaskList class, which aggregates Task objects and holds the ability to add new tasks, edit current tasks, complete tasks, and delete tasks from the list. This class will also have an inherited version called SavedList, which will contain all of the previous information, along with the ability to both save and load information from a file (to maintain information between runs). Since the program is going to be interactive with the user through the terminal, the TaskManager class will be handling all user input and communications with the TaskList object. Functions include writing the menu to an ostream, along with all the menu options, such as editting and sorting the view-type of the list (by category, date, etc.).

> The SOLID principles that we are utilizing for this project, include Single Responsibility Principle, Liskov's Substitution Principle, and Dependency Inversion Principle.
>  * Single Responsibility Principle:
>    * To ensure that our project adheres to SRP, we made sure to divide different uses of our program between different classes. For example, each Task has a due date, but the implementation of the date does not relate to the responsibility of a class that stores Task information. So, we created a helper function Date to manage and initialize correct dates that the Task class will depend on. Similarly, the Task class is unaware of its usage in the program, as its responsibility is to store information (similar to a tuple of strings). As to not violate SRP, we also utilize a TaskList class, which will manage the collection of tasks, and deal with only the addition, deletion, and editing of Tasks in its list. Lastly, we also created a class TaskManager thats responsibility is to communicate between the TaskList and the user, through menus and various prompts. It is unaware of how to manage the list itself, and relies on TaskList to perform these actions correctly.
>  * Liskov's Substitution Principle:
>    * Along with SRP, we wanted our program to follow LSP, and this can be highlighted most prominently through our TaskList class and SavedList inherited class. Our program adheres to LSP, as any place we are able to utilize the base-class TaskList, we are able to utilize the sub-class SavedList with the same implementation. This is most notable in the TaskManager class, as the only member data logged is a TaskList pointer. This can refer to a TaskList object, or a SavedList object, depending on which the user chooses. Since this choice is made by the user, we made sure our program will run as intended despite the choice made.
>  * Dependency Inversion Principle:
>    * Lastly, we wanted to implement DIP into our program, most specifically in the interaction between TaskManager and sorting the TaskList appropriately per the user's choice. We achieved this by developing a "SortList" interface, which consists of a single pure virtual "SortBy" method, able to be defined by each of its sub-classes, SortByDate, and SortByCategory. This way, the high-level module TaskManager is not dependent on the low-level sorting concretions, as they have been abstracted by the SortList interface. Now, in the TaskManager class, we can create a pointer to a SortList object, and can choose which sub-class to fill it with at runtime. 
 
 ## Screenshots
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/94db93a1-107d-4173-90df-555695ae8465)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/101e53cb-20b4-4cbe-afb5-81fecd174b55)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/94b3dfbf-78bf-42b5-8c03-10afd8ac7e28)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/d521dcdb-a054-4b85-9bec-f6950fc734c7)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/568450ba-f755-40bd-9215-f301d3705d87)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/a4b2e914-e57e-4c31-bf37-568af8d754df)
> ![image](https://github.com/cs100/final-project-alamp009-varor004-xwang298-jmin045/assets/147086163/12fa45ae-0ea7-4a19-b8a7-c9c3fc092650)

 ## Installation/Usage
 > To install and run the application, the user should first fork this repository and clone it into an IDE (i.e. VS Code), and then run the following commands: `cmake .` followed by `make` to build the executable. Then to run the program, the user should enter `./all.out` into the terminal. The program relies on user inputs through the keyboard into the console to run, and by following the prompts in the console the user will be able to navigate through the menus, and exit the program when needed.
 ## Testing
 > To test and validate our project, we utilized the googletest framework to write unit tests for our classes. We implemented tests as we were developing new classes to ensure that things were working properly before we merged code and made sure we didn't build on broken code. We did not implement continuous integration for this project, but if we were allotted further time for the project, we would include this to ensure our project doesn't reach a broken state during development. Additionally, we included Valgrind into CMakeFiles so that we could always be checking memory leaks as we were dealing with allocated memory.
 
