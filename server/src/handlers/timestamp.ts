import { Request, Response } from "express";
import timestamp from "../schemas/timestamp";


export const getTimeStamps = async (req: Request, res: Response) => {
    const timestamps = await timestamp.find();
    res.render("pages/index", {timestamps});
}

export const addTimeStamp = async (req: Request, res: Response) => {
    if (!req.body || !req.body.gateOpen || !req.body.gateClosed || !req.body.access_key) {
        return res.json({
            success: false,
            message: "Invalid request body",
        });
    }

    if (req.body.access_key != process.env.ACCESS_KEY) {
        return res.json({
            success: false,
            message: "Incorrect key",
        });
    }

    const ts = new timestamp({
        gateOpen: req.body.gateOpen,
        gateClosed: req.body.gateClosed,
    });

    try {
        const saved = await ts.save();

        return res.json({
            success: true,
            timestamp: saved,
        });
    } catch (err) {
        return res.json({
            success: false,
            message: "DB error",
        });
    }
}