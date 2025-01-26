import customtkinter as ctk
from pages.home import HomePage
from pages.generate import Generate  # Import the Generate page

# Initialize CustomTkinter appearance
ctk.set_appearance_mode("Dark")  # Modes: "System", "Light", "Dark"
ctk.set_default_color_theme("blue")  # Themes: "blue", "green", "dark-blue"





class App(ctk.CTk):
    def __init__(self):
        super().__init__()
        self.title("Generate Classes")
        self.geometry("980x600")

        # Container for all pages
        self.container = ctk.CTkFrame(self, fg_color="transparent")
        self.container.pack(fill="both", expand=True)

        # Dictionary to store frames (pages)disabled
        self.frames = {}

        # Add pages to the container
        for Page in (HomePage, Generate):  # Register both HomePage and Generate
            frame = Page(self.container, self)
            self.frames[Page] = frame
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(HomePage)  # Start with the HomePage

    def show_frame(self, page_class):
        """Raise the given page to the front."""
        if page_class not in self.frames:
            raise KeyError(f"Page {page_class} is not registered.")
        frame = self.frames[page_class]
        frame.tkraise()


if __name__ == "__main__":
    app = App()
    app.mainloop()

