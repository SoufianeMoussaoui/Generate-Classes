import customtkinter as ctk

  # Import Generate for navigation

class HomePage(ctk.CTkFrame):
    def __init__(self, parent, controller):
        super().__init__(parent)
        self.controller = controller

        # Widgets for HomePage
        label = ctk.CTkLabel(self, text="Welcome to the Generate Classes App", 
            font=("Helvetica", 26))
        label.pack(pady=20)

        button = ctk.CTkButton(self, text="Generate Classes",
                               command=lambda: controller.show_frame(Generate))
        button.pack(pady=10)
        
    def exit_app(self):
        # Exit the application
        self.quit()



from pages.generate import Generate






