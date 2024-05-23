# base_parameter.py
class BaseParameter:
    def __init__(self, name, param_type, default_value, description):
        self.name = name
        self.param_type = param_type
        self.default_value = default_value
        self.description = description

    def to_dict(self):
        return {
            "name": self.name,
            "type": self.param_type,
            "default": self.default_value,
            "description": self.description
        }

class FloatParameter(BaseParameter):
    def __init__(self, name, default_value, description, min_value=0.0, max_value=1.0):
        super().__init__(name, "float", default_value, description)
        self.min_value = min_value
        self.max_value = max_value

    def to_dict(self):
        param_dict = super().to_dict()
        param_dict.update({
            "min": self.min_value,
            "max": self.max_value
        })
        return param_dict

class IntParameter(BaseParameter):
    def __init__(self, name, default_value, description, min_value=0, max_value=100):
        super().__init__(name, "int", default_value, description)
        self.min_value = min_value
        self.max_value = max_value

    def to_dict(self):
        param_dict = super().to_dict()
        param_dict.update({
            "min": self.min_value,
            "max": self.max_value
        })
        return param_dict

class BoolParameter(BaseParameter):
    def __init__(self, name, default_value, description):
        super().__init__(name, "bool", default_value, description)

class ColorParameter(BaseParameter):
    def __init__(self, name, default_value, description):
        super().__init__(name, "color", default_value, description)

class ChoiceParameter(BaseParameter):
    def __init__(self, name, default_value, description, options):
        super().__init__(name, "choice", default_value, description)
        self.options = options

    def to_dict(self):
        param_dict = super().to_dict()
        param_dict.update({
            "options": self.options
        })
        return param_dict

# plugin_config.py
class PluginConfig:
    def __init__(self, name, description):
        self.name = name
        self.description = description
        self.parameters = []

    def add_parameter(self, param):
        if isinstance(param, BaseParameter):
            self.parameters.append(param.to_dict())
        else:
            raise TypeError("Parameter must be an instance of BaseParameter")

    def set_processing_function(self, func):
        self.processing_function = func

    def get_config(self):
        return {
            "name": self.name,
            "description": self.description,
            "parameters": self.parameters
        }

    def execute(self, *args, **kwargs):
        if self.processing_function:
            return self.processing_function(*args, **kwargs)
        else:
            raise NotImplementedError("Processing function not set.")