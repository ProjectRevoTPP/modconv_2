#define FORMATS 4

typedef struct {
    std::string path;
    u8 size;
    u8 sizeLog2;
} Texture;

/** Fast3D material class */
class Material
{
    private:
    Texture tex;
    enum TexType { RGBA16, RGBA32, CI4, CI8 };
    enum TexGenType { G_IM_FMT_RGBA, G_IM_FMT_YUV, G_IM_FMT_CI, G_IM_FMT_IA, G_IM_FMT_I };
    enum TexLoadSize { G_IM_SIZ_4b, G_IM_SIZ_8b, G_IM_SIZ_16b, G_IM_SIZ_32b };
    const std::string format[] = { "rgba16", "rgba32", "ci4", "ci8" };
    std::string name = "DEFAULT MATERIAL";

    std::string GetTextureLoad()
    {
        const std::string loadFormat[] = { "G_IM_FMT_RGBA", "G_IM_FMT_YUV", "G_IM_FMT_CI", "G_IM_FMT_IA", "G_IM_FMT_I" };
        const std::string loadFormatsSize[] = { "G_IM_SIZ_4b", "G_IM_SIZ_8b", "G_IM_SIZ_16b", "G_IM_SIZ_32b" };
        //std::string ret;
        //u8 type = 0; /* RGBA16 just in case */
        //for (u8 i = 0; i < FORMATS; i++) {
        //    if (tex.path.find(formats[i]) != std::string::npos) {
        //        type = i;
        //    }
        //}

        /*switch(type) {
            case RGBA32:
            return "gsDPLoadTextureBlock " + getFileNameNoExtension() + ", G_IM_FMT_RGBA, G_IM_SIZ_32b, " + std::to_string(get_dimension(AXIS_X, path)) + ", " + std::to_string(get_dimension(AXIS_Y, path)) + ", 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, " + std::to_string((u16)log2(get_dimension(AXIS_X, path))) + ", " + std::to_string((s16)log2(get_dimension(AXIS_Y, path))) + ", G_TX_NOLOD, G_TX_NOLOD\ngsSPTexture -1, -1, 0, 0, 1\ngsDPTileSync\n";
            break;

            case CI4:
            break;

            case CI8:
            break;

            case RGBA16:
            default:
            return "gsDPLoadTextureBlock " + getFileNameNoExtension() + ", G_IM_FMT_RGBA, G_IM_SIZ_16b, " + std::to_string(get_dimension(AXIS_X, path)) + ", " + std::to_string(get_dimension(AXIS_Y, path)) + ", 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, " + std::to_string((u16)log2(get_dimension(AXIS_X, path))) + ", " + std::to_string((s16)log2(get_dimension(AXIS_Y, path))) + ", G_TX_NOLOD, G_TX_NOLOD\ngsSPTexture -1, -1, 0, 0, 1\ngsDPTileSync\n";
        }*/
        return ""; /* ok cuck */
    }

    /** Returns combiner settings. */
    std::string GetFuckingFrauber() /** TODO: Get this to support fog, semitransparency, and both if possible. */
    {
        if (textured) {
            return "gsDPSetCombineMode1Cycle G_CCMUX_TEXEL0, G_CCMUX_0, G_CCMUX_SHADE, G_CCMUX_0, G_ACMUX_0, G_ACMUX_0, G_ACMUX_0, G_ACMUX_SHADE\n";
        }

        else {
            return "gsDPSetCombineMode1Cycle G_CCMUX_PRIMITIVE, G_CCMUX_0, G_CCMUX_SHADE, G_CCMUX_0, G_ACMUX_0, G_ACMUX_0, G_ACMUX_0, G_ACMUX_SHADE\n";
        }
    }

    public:
    bool useless = false, textured = false;
    void setName(const std::string &n) { name = n; }
    void setPath(const std::string &p)
    {
        tex.path = p;
    }

    std::string getPath() { return tex.path; }
    std::string getName() { return name; }


    std::string getFileNameNoExtension()
    {
        std::string toReturn = get_filename(tex.path);
        return toReturn.substr(0, toReturn.length() - 4); /* <- Hack */
    }

    /** Configures the Material object. (Unused for now) */
    void setMaterial(std::string n, std::string p) {}

    /** Returns the incbins. */
    std::string d;
    /** Returns the exact F3D settings that represent this material. */
    std::string getMaterial()
    {
        std::string ret;
        if (textured) {
            ret = GetFuckingFrauber() + GetTextureLoad();
        }

        else { /* no texture found when setting up */
            ret = GetFuckingFrauber() + "gsDPSetPrimColor 0x00, 0x00, 128, 128, 128, 0xFF\n";
        }
        return ret;
    }
};
