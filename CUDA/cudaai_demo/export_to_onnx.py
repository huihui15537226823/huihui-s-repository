import torch
import torchvision.models as models

# 加载预训练模型
model = models.resnet50(weights=models.ResNet50_Weights.DEFAULT)
model.eval()  # 设置为推理模式

# 创建一个虚拟输入，用于定义模型结构
dummy_input = torch.randn(1, 3, 224, 224)

# 导出为 ONNX 格式
torch.onnx.export(
    model,
    dummy_input,
    "resnet50.onnx",
    input_names=["input"],  # 输入节点名称
    output_names=["output"],  # 输出节点名称
    dynamic_axes={"input": {0: "batch"}, "output": {0: "batch"}},  # 可变 batch
    opset_version=17
)

print("✅ 模型成功导出为 resnet50.onnx")