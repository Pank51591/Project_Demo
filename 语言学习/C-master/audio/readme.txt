这里用于编码和解码的A-law算法（16bit pcm<=>A-law）。

该算法是将16bits的pcm信号编码成8bits样本进行传输，有基于G.711标准的两种算法（A-law, u-law）。本文采用第一种。