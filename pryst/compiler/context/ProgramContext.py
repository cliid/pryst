class ProgramContext:
    functions = {}

    def add_function(self, name, pointer):
        self.functions[name] = pointer

    def get_function(self, name):
        return self.functions[name]
