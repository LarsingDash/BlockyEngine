import gdb

class GameObjectPrinter:
    def __init__(self, val):
        self.val = val
        
    def to_string(self):
        tag = self.val['tag']
        return f"{tag} - {self.val.address}"

def lookup_type(val):
    if str(val.type) == 'GameObject *':
        return GameObjectPrinter(val)
    return None

gdb.pretty_printers.append(lookup_type)
