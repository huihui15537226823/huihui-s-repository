import onnxruntime as ort
import numpy as np
import time

# 1. 创建 ONNX Runtime 推理会话
session = ort.InferenceSession("resnet50.onnx", providers=['CUDAExecutionProvider'])

# 2. 准备测试输入
dummy_input = np.random.randn(1, 3, 224, 224).astype(np.float32)

# 3. 运行推理
start = time.time()
outputs = session.run(None, {"input": dummy_input})
print("✅ 模型运行成功！推理耗时：", round(time.time() - start, 4), "秒")

# 4. 输出结果维度
print("输出形状：", np.array(outputs[0]).shape)
