//=========================//
//	ジオメトリシェーダ(2)
//=========================//
#include "Particle.hlsli"

//	四角形の頂点数
static const uint vnum = 4;

//	中心点からのオフセット
static const float4 offset_array[vnum] =
{
    float4(-0.5f, -0.5f, 0, 0), //左下
	float4(+0.5f, -0.5f, 0, 0), //右下
	float4(-0.5f, +0.5f, 0, 0), //左上
	float4(+0.5f, +0.5f, 0, 0) //右上
};

//	テクスチャUV(左上が00、右下が11)
static const float2 uv_array[vnum] =
{
    float2(0.0f, 1.0f), //左下
	float2(1.0f, 1.0f), //右下
	float2(0.0f, 0.0f), //左上
	float2(1.0f, 0.0f) //右上
};

//頂点の最大数
[maxvertexcount(vnum)]
void main(
	point GSInput input[1],
	inout TriangleStream<PSInput> output)
{
    PSInput element;
    float4 offset;

    float scale = input[0].other.x;
    float rot = input[0].other.y;

		//	4点分
    for (uint i = 0; i < vnum; i++)
    {
			//	指定角度分の回転
        offset.x = offset_array[i].x * cos(rot) + offset_array[i].y * sin(rot);
        offset.y = offset_array[i].x * -sin(rot) + offset_array[i].y * cos(rot);
        offset.z = 0;
        offset.w = 0;
			//	スケーリング
        offset = offset * scale;
			//	ビルボード回転
        offset = mul(offset, g_Billboard);
			//	平行行列
        element.pos = input[0].pos + offset;
			//	ワールド座標→２Ⅾに変換
        element.pos = mul(element.pos, g_WVP);
        element.color = input[0].color;
        element.uv = uv_array[i];
        output.Append(element);
    }

		//	プリミティブの区切り
    output.RestartStrip();
}
