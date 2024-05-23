from enum import Enum
import json
from typing import List, Dict, Any

class Item:
    def __init__(self, name: str, description: str):
        self.name = name
        self.description = description
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            "name": self.name,
            "description": self.description
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'Item':
        return Item(data["name"], data["description"])
    
    def __str__(self):
        return f"{self.name}: {self.description}"
    
    def __repr__(self):
        return str(self)
    
class Tradeable_Item(Item):
    def __init__(self, name: str, description: str, price: int):
        super().__init__(name, description)
        self.price = price
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            **super().to_dict(),
            "price": self.price
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'Tradeable_Item':
        return Tradeable_Item(data["name"], data["description"], data["price"])
    
    def __str__(self):
        return f"{self.name}: {self.description} - {self.price}"
    
    def __repr__(self):
        return str(self)
    
class UnTradeable_Item(Item):
    def __init__(self, name: str, description: str, rarity: int):
        super().__init__(name, description)
        self.rarity = rarity
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            **super().to_dict(),
            "rarity": self.rarity
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'UnTradeable_Item':
        return UnTradeable_Item(data["name"], data["description"], data["rarity"])
    
    def __str__(self):
        return f"{self.name}: {self.description} - {self.rarity}"
    
    def __repr__(self):
        return str(self)
    
class Item_Type(Enum):
    TRADEABLE = 1
    UNTRADEABLE = 2
    
class Inventory:
    def __init__(self):
        self.items = []
        
    def add_item(self, item: Item):
        self.items.append(item)
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            "items": [item.to_dict() for item in self.items]
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'Inventory':
        inventory = Inventory()
        for item_data in data["items"]:
            if "price" in item_data:
                inventory.add_item(Tradeable_Item.from_dict(item_data))
            else:
                inventory.add_item(UnTradeable_Item.from_dict(item_data))
        return inventory
    
    def __str__(self):
        return "\n".join(str(item) for item in self.items)
    
    def __repr__(self):
        return str(self)
    
class Character:
    def __init__(self, name: str, health: int, max_health: int, stamina: int, max_stamina: int, inventory: Inventory):
        self.name = name
        self.health = health
        self.max_health = max_health
        self.stamina = stamina
        self.max_stamina = max_stamina
        self.inventory = inventory
        
    def add_health(self, health: int):
        self.health = min(self.health + health, self.max_health)
        
    def add_stamina(self, stamina: int):
        self.stamina = min(self.stamina + stamina, self.max_stamina)
        
    def remove_health(self, health: int):
        self.health = max(self.health - health, 0)
        
    def remove_stamina(self, stamina: int):
        self.stamina = max(self.stamina - stamina, 0)
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            "name": self.name,
            "health": self.health,
            "max_health": self.max_health,
            "stamina": self.stamina,
            "max_stamina": self.max_stamina,
            "inventory": self.inventory.to_dict()
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'Character':
        return Character(data["name"], data["health"], data["max_health"], data["stamina"], data["max_stamina"], Inventory.from_dict(data["inventory"]))
    
    def __str__(self):
        return f"{self.name}: {self.health}/{self.max_health}HP, {self.stamina}/{self.max_stamina}STAMINA\n{self.inventory}"
    
    def __repr__(self):
        return str(self)
    
class State(Enum):
    HOSTILE = 1
    NEUTRAL = 2
    FRIENDLY = 3
    
class NPC(Character):
    def __init__(self, name: str, health: int, max_health: int, stamina: int, max_stamina: int, inventory: Inventory, state: State):
        super().__init__(name, health, max_health, stamina, max_stamina, inventory)
        self.state = state
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            **super().to_dict(),
            "state": self.state.value
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'NPC':
        return NPC(data["name"], data["health"], data["max_health"], data["stamina"], data["max_stamina"], Inventory.from_dict(data["inventory"]), State(data["state"]))
    
    def __str__(self):
        return f"{self.name}: {self.health}/{self.max_health}HP, {self.stamina}/{self.max_stamina}STAMINA\n{self.inventory}\nState: {self.state.name}"
    
    def __repr__(self):
        return str(self)
    
class Player(Character):
    def __init__(self, name: str, health: int, max_health: int, stamina: int, max_stamina: int, inventory: Inventory, level: int):
        super().__init__(name, health, max_health, stamina, max_stamina, inventory)
        self.level = level
        
    def to_dict(self) -> Dict[str, Any]:
        return {
            **super().to_dict(),
            "level": self.level
        }
        
    @staticmethod
    def from_dict(data: Dict[str, Any]) -> 'Player':
        return Player(data["name"], data["health"], data["max_health"], data["stamina"], data["max_stamina"], Inventory.from_dict(data["inventory"]), data["level"])
    
    def __str__(self):
        return f"{self.name}: {self.health}/{self.max_health}HP, {self.stamina}/{self.max_stamina}STAMINA\n{self.inventory}\nLevel: {self.level}"
    
    def __repr__(self):
        return str(self)
    
        
    