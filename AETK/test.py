
import sys
sys.path.append(r"C:\Users\tjerf\source\repos\AETK\AETK\Python")

import After_Effects as ae

item = ae.Item.active_item()

if isinstance(item, ae.CompItem):
    ae.App().report_info(f"CompItem: {item.name}")
    layers : ae.LayerCollection = item.layers
    for layer in layers:
        pos = layer.position
        ae.App().report_info(f"Layer: {layer.name} {pos[0]}")
        
elif isinstance(item, ae.FootageItem):
    ae.App().report_info(f"FootageItem: {item.name}")
else:
    ae.App().report_info(f"Item: {item.name}")
    
    