import customtkinter as ctk
 # Import HomePage for navigation


class Generate(ctk.CTkFrame):
    def __init__(self, parent, controller):
        super().__init__(parent)
        self.controller = controller

        # Configure grid to allow centering
        self.grid_rowconfigure(0, weight=1)  # Center vertically
        self.grid_columnconfigure(0, weight=1)  # Center horizontally

        # Widgets for Generate Page
        label = ctk.CTkLabel(self, text="This is the Generate Page", font=("Helvetica", 16))
        label.grid(row=0, column=0, sticky="nsew")  # Center the label

        self.class_name_label = ctk.CTkLabel(self, text="Enter Class Name:")
        self.class_name_label.grid(row=1, column=0, pady=(10, 5))  # Position below the label
        
        self.class_name_entry = ctk.CTkEntry(self, placeholder_text="Class Name", width=300)
        self.class_name_entry.grid(row=2, column=0, pady=(0, 20))  # Position below the label

        self.error_class_name = ctk.CTkLabel(self, text="Please enter a class name.", state ="disabled")
        #self.error_class_name.grid(row=4, column=0, pady=(10, 5))
        # Submit button
        self.submit_button = ctk.CTkButton(self, text="Submit", command=self.submit_class_name)
        self.submit_button.grid(row=3, column=0, pady=10)
    
        


        button = ctk.CTkButton(self, text="Back to Home",
                               command=lambda: controller.show_frame(HomePage))
        button.grid(row=10, column=10, pady=20)  # Place button below label, still centered

        # Adjust row weight for button placement
        self.grid_rowconfigure(5, weight=0)  # Make sure the button is below, not stretched

    def submit_class_name(self):
        """Submit the entered class name."""
        class_name = self.class_name_entry.get()
        if class_name:
            self.error_class_name.configure(state="disabled") 
            return class_name
         
        else:
            self.error_class_name.configure(state="normal")  # Make error message visible
            self.error_class_name.grid(row=4, column=0, pady=(10, 5)) 



from pages.home import HomePage 

"""

create a instance of the class 

set the class name enter

 call createFile function






"""



